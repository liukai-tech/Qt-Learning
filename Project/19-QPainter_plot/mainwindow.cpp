#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GraphT =new Graph(ui->labelDrawPath);
    GraphT->Fit=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

// callback for painting   --------------------------------------------------
void MainWindow::paintEvent(QPaintEvent *)
{
    UpdateDisp();
}

// update plot --------------------------------------------------------------
void MainWindow::UpdatePlot(void)
{
    Refresh();
}
// refresh plot -------------------------------------------------------------
void MainWindow::Refresh(void)
{
    Flush=1;
    UpdateDisp();
    ui->labelDrawPath->update();
}
// draw plot ----------------------------------------------------------------
void MainWindow::UpdateDisp(void)
{
    int level=Drag?0:1;

    if (Flush) {
        Buff=QPixmap(ui->labelDrawPath->size());
        if (Buff.isNull()) return;
        Buff.fill(CColor[0]);

        QPainter c(&Buff);

        c.setFont(ui->labelDrawPath->font());
        c.setPen(CColor[0]);
        c.setBrush(CColor[0]);

        DrawTrk(c,level);

        ui->labelDrawPath->setPixmap(Buff);
    }

    Flush=0;
}
// draw track-plot ----------------------------------------------------------
void MainWindow::DrawTrk(QPainter &c,int level)
{
    QString label,header;
    TIMEPOS *pos,*pos1,*pos2,*vel;
    gtime_t time1={0,0},time2={0,0};
    sol_t *sol;
    QPoint p1,p2;
    double xt,yt,sx,sy,opos[3],pnt[3],rr[3],enu[3],cent[3];
    int i,sel=!BtnSol1->isChecked()&&BtnSol2->isChecked()?1:0,p=0;

    trace(3,"DrawTrk: level=%d\n",level);

    if (BtnShowTrack->isChecked()&&BtnFixCent->isChecked()) {
        if (!BtnSol12->isChecked()) {
            pos=SolToPos(SolData+sel,SolIndex[sel],0,0);
            if (pos->n>0) GraphT->SetCent(pos->x[0],pos->y[0]);
            delete pos;
        }
        else {
            pos1=SolToPos(SolData  ,SolIndex[0],0,0);
            pos2=SolToPos(SolData+1,SolIndex[1],0,0);
            pos=pos1->diff(pos2,0);
            if (pos->n>0) GraphT->SetCent(pos->x[0],pos->y[0]);
            delete pos;
            delete pos1;
            delete pos2;
        }
    }
    if (!BtnSol12->isChecked()&&BtnShowImg->isChecked()) {// image
        DrawTrkImage(c,level);
    }
    if (BtnShowMap->isChecked()) {// map
        DrawTrkMap(c,level);
    }
    if (level) { // center +
        GraphT->GetPos(p1,p2);
        p1.rx()=(p1.x()+p2.x())/2;
        p1.ry()=(p1.y()+p2.y())/2;
        DrawMark(GraphT,c,p1,5,CColor[1],20,0);
    }
    if (ShowGLabel>=3) {// circles
        GraphT->XLPos=7; GraphT->YLPos=7;
        GraphT->DrawCircles(c,ShowGLabel==4);
    }
    else if (ShowGLabel>=1) {// grid
        GraphT->XLPos=2; GraphT->YLPos=4;
        GraphT->DrawAxis(c,ShowLabel,ShowGLabel==2);
    }

    if (norm(OPos,3)>0.0) {
        ecef2pos(OPos,opos);
        header="ORI="+LatLonStr(opos,9)+QString(" %1m").arg(opos[2],0,'f',4);
    }
    if (BtnSol1->isChecked()) {
        pos=SolToPos(SolData,-1,QFlag->currentIndex(),0);
        DrawTrkPnt(c,pos,level,0);
        if (BtnShowMap->isChecked()) {
            DrawTrkPos(c,SolData[0].rb,0,8,CColor[2],tr("Base Station 1"));
        }
        DrawTrkStat(c,pos,header,p++);
        header="";
        delete pos;
    }
    if (BtnSol2->isChecked()) {
        pos=SolToPos(SolData+1,-1,QFlag->currentIndex(),0);
        DrawTrkPnt(c,pos,level,1);
        if (BtnShowMap->isChecked()) {
            DrawTrkPos(c,SolData[1].rb,0,8,CColor[2],tr("Base Station 2"));
        }
        DrawTrkStat(c,pos,header,p++);
        delete pos;
    }
    if (BtnSol12->isChecked()) {
        pos1=SolToPos(SolData  ,-1,0,0);
        pos2=SolToPos(SolData+1,-1,0,0);
        pos=pos1->diff(pos2,QFlag->currentIndex());
        DrawTrkPnt(c,pos,level,0);
        DrawTrkStat(c,pos,"",p++);
        delete pos;
        delete pos1;
        delete pos2;
    }
    if (BtnShowTrack->isChecked()&&BtnSol1->isChecked()) {

        pos=SolToPos(SolData,SolIndex[0],0,0);

        if ((sol=getsol(SolData,SolIndex[0]))) time1=sol->time;

        if (pos->n) {
            pos->n=1;
            DrawTrkError(c,pos,0);
            GraphT->ToPoint(pos->x[0],pos->y[0],p1);
            GraphT->DrawMark(c,p1,0,CColor[0],MarkSize*2+12,0);
            GraphT->DrawMark(c,p1,1,CColor[2],MarkSize*2+10,0);
            GraphT->DrawMark(c,p1,5,CColor[2],MarkSize*2+14,0);
            GraphT->DrawMark(c,p1,0,CColor[2],MarkSize*2+6,0);
            GraphT->DrawMark(c,p1,0,MColor[0][pos->q[0]],MarkSize*2+4,0);
            if (BtnSol2->isChecked()) {
                p1.rx()+=MarkSize+8;
                DrawLabel(GraphT,c,p1,"1",1,0);
            }
        }
        delete pos;
    }
    if (BtnShowTrack->isChecked()&&BtnSol2->isChecked()) {

        pos=SolToPos(SolData+1,SolIndex[1],0,0);

        if ((sol=getsol(SolData+1,SolIndex[1]))) time2=sol->time;

        if (pos->n>0&&(time1.time==0||fabs(timediff(time1,time2))<DTTOL*2.0)) {
            pos->n=1;
            DrawTrkError(c,pos,1);
            GraphT->ToPoint(pos->x[0],pos->y[0],p1);
            GraphT->DrawMark(c,p1,0,CColor[0],MarkSize*2+12,0);
            GraphT->DrawMark(c,p1,1,CColor[1],MarkSize*2+10,0);
            GraphT->DrawMark(c,p1,5,CColor[1],MarkSize*2+14,0);
            GraphT->DrawMark(c,p1,0,CColor[2],MarkSize*2+6,0);
            GraphT->DrawMark(c,p1,0,MColor[1][pos->q[0]],MarkSize*2+4,0);
            if (BtnSol1->isChecked()) {
                p1.setX(p1.x()+MarkSize+8);
                DrawLabel(GraphT,c,p1,"2",1,0);
            }
        }
        delete pos;
    }
    if (BtnShowTrack->isChecked()&&BtnSol12->isChecked()) {

        pos1=SolToPos(SolData  ,SolIndex[0],0,0);
        pos2=SolToPos(SolData+1,SolIndex[1],0,0);
        pos=pos1->diff(pos2,0);

        if (pos->n>0) {
            pos->n=1;
            DrawTrkError(c,pos,1);
            GraphT->ToPoint(pos->x[0],pos->y[0],p1);
            GraphT->DrawMark(c,p1,0,CColor[0],MarkSize*2+12,0);
            GraphT->DrawMark(c,p1,1,CColor[2],MarkSize*2+10,0);
            GraphT->DrawMark(c,p1,5,CColor[2],MarkSize*2+14,0);
            GraphT->DrawMark(c,p1,0,CColor[2],MarkSize*2+6,0);
            GraphT->DrawMark(c,p1,0,MColor[0][pos->q[0]],MarkSize*2+4,0);
        }
        delete pos;
        delete pos1;
        delete pos2;
    }
    if (BtnShowMap->isChecked()) {
        for (i=0;i<NWayPnt;i++) {
            pnt[0]=PntPos[i][0]*D2R;
            pnt[1]=PntPos[i][1]*D2R;
            pnt[2]=PntPos[i][2];
            pos2ecef(pnt,rr);
            DrawTrkPos(c,rr,0,i==SelWayPnt?12:8,CColor[2],PntName[i]);
        }
    }

    if (ShowCompass) {
        GraphT->GetPos(p1,p2);
        p1.rx()+=SIZE_COMP/2+25;
        p1.ry()+=SIZE_COMP/2+35;
        DrawMark(GraphT,c,p1,13,CColor[2],SIZE_COMP,0);
    }
    if (ShowArrow&&BtnShowTrack->isChecked()) {
        vel=SolToPos(SolData+sel,SolIndex[sel],0,1);
        DrawTrkVel(c,vel);
        delete vel;
    }
    if (ShowScale) {
        GraphT->GetPos(p1,p2);
        GraphT->GetTick(xt,yt);
        GraphT->GetScale(sx,sy);
        p2.rx()-=70;
        p2.ry()-=25;
        DrawMark(GraphT,c,p2,11,CColor[2],static_cast<int>(xt/sx+0.5),0);
        p2.ry()-=3;
        if      (xt<0.01  ) label=QString("%1 mm").arg(xt*1000.0,0,'f',0);
        else if (xt<1.0   ) label=QString("%1 cm").arg(xt*100.0,0,'f',0);
        else if (xt<1000.0) label=QString("%1 m" ).arg(xt,0,'f',0);
        else                label=QString("%1 km").arg(xt/1000.0,0,'f',0);
        DrawLabel(GraphT,c,p2,label,0,1);
    }

    if (!level) { // center +
        GraphT->GetCent(xt,yt);
        GraphT->ToPoint(xt,yt,p1);
        DrawMark(GraphT,c,p1,5,CColor[2],20,0);
    }
    // update geview and gmview center
    if (level&&norm(OPos,3)>0.0) {
        GraphT->GetCent(xt,yt);
        GraphT->ToPoint(xt,yt,p1);
        GraphT->ToPos(p1,enu[0],enu[1]);
        enu[2]=0;
        ecef2pos(OPos,opos);
        enu2ecef(opos,enu,rr);
        for (i=0;i<3;i++) rr[i]+=OPos[i];
        ecef2pos(rr,cent);

        googleEarthView->SetCent(cent[0]*R2D,cent[1]*R2D);
        googleMapView->SetCent(cent[0]*R2D,cent[1]*R2D);
    }
    Refresh_GEView();
}
