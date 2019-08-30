
#include <stdio.h>
#include <math.h>

int vbic_3T_it_xf_f(p
	,Vbei,Vbex,Vbci,Vbep,Vrxf,Vrcx
	,Vbcx,Vrci,Vrbx,Vrbi,Vre,Vrbp,Vbe
	,Vbc,Vcxf,Ibe,Ibex,Itxf,Itzr,Ibc
	,Ibep,Ircx,Irci,Irbx,Irbi,Ire,Irbp
	,Qbe,Qbex,Qbc,Qbcx,Qbep,Qbeo,Qbco
	,Ixzf,Ixxf,Qcxf,Flxf,SCALE)
double *p
	,*Vbei,*Vbex,*Vbci,*Vbep,*Vrxf,*Vrcx
	,*Vbcx,*Vrci,*Vrbx,*Vrbi,*Vre,*Vrbp,*Vbe
	,*Vbc,*Vcxf,*Ibe,*Ibex,*Itxf,*Itzr,*Ibc
	,*Ibep,*Ircx,*Irci,*Irbx,*Irbi,*Ire,*Irbp
	,*Qbe,*Qbex,*Qbc,*Qbcx,*Qbep,*Qbeo,*Qbco
	,*Ixzf,*Ixxf,*Qcxf,*Flxf,*SCALE;
{
double	Vtv,IVEF,IVER,IIKF,IIKR,IIKP,IVO;
double	IHRCF,IVTF,IITF,slTF,LEP,CEP,dv0;
double	dvh,xvar1,xvar2,pwq,qlo,qhi,xvar3;
double	qdbe,mv0,vl0,q0,dv,mv,vl;
double	qdbex,qdbc,vn0,vnl0,qlo0,vn,vnl;
double	sel,crt,cmx,cl,ql,qdbep,argi;
double	expi,Ifi,Iri,q1z,q1,q2,xvar4;
double	qb,Itzf,argx,expx,Ifp,q2p,qbp;
double	argn,expn,Ibcj,avalf,Igc,Kbci,Kbcx;
double	rKp1,Iohm,derf,sgIf,rIf,mIf,tff;

/*	Function only code */

	Vtv=1.380662e-23*(2.731500e+02+p[0])/1.602189e-19;
	if(p[51]>0.0){
		IVEF=1.0/p[51];
	}else{
		IVEF=0.0;
	}
	if(p[52]>0.0){
		IVER=1.0/p[52];
	}else{
		IVER=0.0;
	}
	if(p[53]>0.0){
		IIKF=1.0/p[53];
	}else{
		IIKF=0.0;
	}
	if(p[54]>0.0){
		IIKR=1.0/p[54];
	}else{
		IIKR=0.0;
	}
	if(p[55]>0.0){
		IIKP=1.0/p[55];
	}else{
		IIKP=0.0;
	}
	if(p[3]>0.0){
		IVO=1.0/p[3];
	}else{
		IVO=0.0;
	}
	if(p[5]>0.0){
		IHRCF=1.0/p[5];
	}else{
		IHRCF=0.0;
	}
	if(p[59]>0.0){
		IVTF=1.0/p[59];
	}else{
		IVTF=0.0;
	}
	if(p[60]>0.0){
		IITF=1.0/p[60];
	}else{
		IITF=0.0;
	}
	if(p[60]>0.0){
		slTF=0.0;
	}else{
		slTF=1.0;
	}
	if(p[62]>0.0){
		LEP=p[62]/3.0;
	}else{
		LEP=0.0;
	}
	if(p[62]>0.0){
		CEP=p[62];
	}else{
		CEP=0.0;
	}
	dv0=-p[17]*p[14];
	if(p[19]<=0.0){
		dvh=(*Vbei)+dv0;
		if(dvh>0.0){
			xvar1=(1.0-p[14]);
			xvar2=(-1.0-p[18]);
			pwq=pow(xvar1,xvar2);
			qlo=p[17]*(1.0-pwq*(1.0-p[14])*(1.0-p[14]))/(1.0-p[18]);
			qhi=dvh*(1.0-p[14]+0.5*p[18]*dvh/p[17])*pwq;
		}else{
			xvar1=(1.0-(*Vbei)/p[17]);
			xvar2=(1.0-p[18]);
			xvar3=pow(xvar1,xvar2);
			qlo=p[17]*(1.0-xvar3)/(1.0-p[18]);
			qhi=0.0;
		}
		qdbe=qlo+qhi;
	}else{
		mv0=sqrt(dv0*dv0+4.0*p[19]*p[19]);
		vl0=-0.5*(dv0+mv0);
		xvar1=(1.0-vl0/p[17]);
		xvar2=(1.0-p[18]);
		xvar3=pow(xvar1,xvar2);
		q0=-p[17]*xvar3/(1.0-p[18]);
		dv=(*Vbei)+dv0;
		mv=sqrt(dv*dv+4.0*p[19]*p[19]);
		vl=0.5*(dv-mv)-dv0;
		xvar1=(1.0-vl/p[17]);
		xvar2=(1.0-p[18]);
		xvar3=pow(xvar1,xvar2);
		qlo=-p[17]*xvar3/(1.0-p[18]);
		xvar1=(1.0-p[14]);
		xvar2=(-p[18]);
		xvar3=pow(xvar1,xvar2);
		qdbe=qlo+xvar3*((*Vbei)-vl+vl0)-q0;
	}
	dv0=-p[17]*p[14];
	if(p[19]<=0.0){
		dvh=(*Vbex)+dv0;
		if(dvh>0.0){
			xvar1=(1.0-p[14]);
			xvar2=(-1.0-p[18]);
			pwq=pow(xvar1,xvar2);
			qlo=p[17]*(1.0-pwq*(1.0-p[14])*(1.0-p[14]))/(1.0-p[18]);
			qhi=dvh*(1.0-p[14]+0.5*p[18]*dvh/p[17])*pwq;
		}else{
			xvar1=(1.0-(*Vbex)/p[17]);
			xvar2=(1.0-p[18]);
			xvar3=pow(xvar1,xvar2);
			qlo=p[17]*(1.0-xvar3)/(1.0-p[18]);
			qhi=0.0;
		}
		qdbex=qlo+qhi;
	}else{
		mv0=sqrt(dv0*dv0+4.0*p[19]*p[19]);
		vl0=-0.5*(dv0+mv0);
		xvar1=(1.0-vl0/p[17]);
		xvar2=(1.0-p[18]);
		xvar3=pow(xvar1,xvar2);
		q0=-p[17]*xvar3/(1.0-p[18]);
		dv=(*Vbex)+dv0;
		mv=sqrt(dv*dv+4.0*p[19]*p[19]);
		vl=0.5*(dv-mv)-dv0;
		xvar1=(1.0-vl/p[17]);
		xvar2=(1.0-p[18]);
		xvar3=pow(xvar1,xvar2);
		qlo=-p[17]*xvar3/(1.0-p[18]);
		xvar1=(1.0-p[14]);
		xvar2=(-p[18]);
		xvar3=pow(xvar1,xvar2);
		qdbex=qlo+xvar3*((*Vbex)-vl+vl0)-q0;
	}
	dv0=-p[24]*p[14];
	if(p[26]<=0.0){
		dvh=(*Vbci)+dv0;
		if(dvh>0.0){
			xvar1=(1.0-p[14]);
			xvar2=(-1.0-p[25]);
			pwq=pow(xvar1,xvar2);
			qlo=p[24]*(1.0-pwq*(1.0-p[14])*(1.0-p[14]))/(1.0-p[25]);
			qhi=dvh*(1.0-p[14]+0.5*p[25]*dvh/p[24])*pwq;
		}else{
			if((p[85]>0.0)&&((*Vbci)<-p[85])){
				xvar1=(1.0+p[85]/p[24]);
				xvar2=(1.0-p[25]);
				xvar3=pow(xvar1,xvar2);
				qlo=p[24]*(1.0-xvar3*(1.0-((1.0-p[25])*((*Vbci)+p[85]))/(p[24]+p[85])))/(1.0-p[25]);
			}else{
				xvar1=(1.0-(*Vbci)/p[24]);
				xvar2=(1.0-p[25]);
				xvar3=pow(xvar1,xvar2);
				qlo=p[24]*(1.0-xvar3)/(1.0-p[25]);
			}
			qhi=0.0;
		}
		qdbc=qlo+qhi;
	}else{
		if((p[85]>0.0)&&(p[86]>0.0)){
			vn0=(p[85]+dv0)/(p[85]-dv0);
			vnl0=2.0*vn0/(sqrt((vn0-1.0)*(vn0-1.0)+4.0*p[26]*p[26])+sqrt((vn0+1.0)*(vn0+1.0)+4.0*p[86]*p[86]));
			vl0=0.5*(vnl0*(p[85]-dv0)-p[85]-dv0);
			xvar1=(1.0-vl0/p[24]);
			xvar2=(1.0-p[25]);
			xvar3=pow(xvar1,xvar2);
			qlo0=p[24]*(1.0-xvar3)/(1.0-p[25]);
			vn=(2.0*(*Vbci)+p[85]+dv0)/(p[85]-dv0);
			vnl=2.0*vn/(sqrt((vn-1.0)*(vn-1.0)+4.0*p[26]*p[26])+sqrt((vn+1.0)*(vn+1.0)+4.0*p[86]*p[86]));
			vl=0.5*(vnl*(p[85]-dv0)-p[85]-dv0);
			xvar1=(1.0-vl/p[24]);
			xvar2=(1.0-p[25]);
			xvar3=pow(xvar1,xvar2);
			qlo=p[24]*(1.0-xvar3)/(1.0-p[25]);
			sel=0.5*(vnl+1.0);
			xvar1=(1.0+p[85]/p[24]);
			xvar2=(-p[25]);
			crt=pow(xvar1,xvar2);
			xvar1=(1.0+dv0/p[24]);
			xvar2=(-p[25]);
			cmx=pow(xvar1,xvar2);
			cl=(1.0-sel)*crt+sel*cmx;
			ql=((*Vbci)-vl+vl0)*cl;
			qdbc=ql+qlo-qlo0;
		}else{
			mv0=sqrt(dv0*dv0+4.0*p[26]*p[26]);
			vl0=-0.5*(dv0+mv0);
			xvar1=(1.0-vl0/p[24]);
			xvar2=(1.0-p[25]);
			xvar3=pow(xvar1,xvar2);
			q0=-p[24]*xvar3/(1.0-p[25]);
			dv=(*Vbci)+dv0;
			mv=sqrt(dv*dv+4.0*p[26]*p[26]);
			vl=0.5*(dv-mv)-dv0;
			xvar1=(1.0-vl/p[24]);
			xvar2=(1.0-p[25]);
			xvar3=pow(xvar1,xvar2);
			qlo=-p[24]*xvar3/(1.0-p[25]);
			xvar1=(1.0-p[14]);
			xvar2=(-p[25]);
			xvar3=pow(xvar1,xvar2);
			qdbc=qlo+xvar3*((*Vbci)-vl+vl0)-q0;
		}
	}
	dv0=-p[24]*p[14];
	if(p[26]<=0.0){
		dvh=(*Vbep)+dv0;
		if(dvh>0.0){
			xvar1=(1.0-p[14]);
			xvar2=(-1.0-p[25]);
			pwq=pow(xvar1,xvar2);
			qlo=p[24]*(1.0-pwq*(1.0-p[14])*(1.0-p[14]))/(1.0-p[25]);
			qhi=dvh*(1.0-p[14]+0.5*p[25]*dvh/p[24])*pwq;
		}else{
			if((p[85]>0.0)&&((*Vbep)<-p[85])){
				xvar1=(1.0+p[85]/p[24]);
				xvar2=(1.0-p[25]);
				xvar3=pow(xvar1,xvar2);
				qlo=p[24]*(1.0-xvar3*(1.0-((1.0-p[25])*((*Vbep)+p[85]))/(p[24]+p[85])))/(1.0-p[25]);
			}else{
				xvar1=(1.0-(*Vbep)/p[24]);
				xvar2=(1.0-p[25]);
				xvar3=pow(xvar1,xvar2);
				qlo=p[24]*(1.0-xvar3)/(1.0-p[25]);
			}
			qhi=0.0;
		}
		qdbep=qlo+qhi;
	}else{
		if((p[85]>0.0)&&(p[86]>0.0)){
			vn0=(p[85]+dv0)/(p[85]-dv0);
			vnl0=2.0*vn0/(sqrt((vn0-1.0)*(vn0-1.0)+4.0*p[26]*p[26])+sqrt((vn0+1.0)*(vn0+1.0)+4.0*p[86]*p[86]));
			vl0=0.5*(vnl0*(p[85]-dv0)-p[85]-dv0);
			xvar1=(1.0-vl0/p[24]);
			xvar2=(1.0-p[25]);
			xvar3=pow(xvar1,xvar2);
			qlo0=p[24]*(1.0-xvar3)/(1.0-p[25]);
			vn=(2.0*(*Vbep)+p[85]+dv0)/(p[85]-dv0);
			vnl=2.0*vn/(sqrt((vn-1.0)*(vn-1.0)+4.0*p[26]*p[26])+sqrt((vn+1.0)*(vn+1.0)+4.0*p[86]*p[86]));
			vl=0.5*(vnl*(p[85]-dv0)-p[85]-dv0);
			xvar1=(1.0-vl/p[24]);
			xvar2=(1.0-p[25]);
			xvar3=pow(xvar1,xvar2);
			qlo=p[24]*(1.0-xvar3)/(1.0-p[25]);
			sel=0.5*(vnl+1.0);
			xvar1=(1.0+p[85]/p[24]);
			xvar2=(-p[25]);
			crt=pow(xvar1,xvar2);
			xvar1=(1.0+dv0/p[24]);
			xvar2=(-p[25]);
			cmx=pow(xvar1,xvar2);
			cl=(1.0-sel)*crt+sel*cmx;
			ql=((*Vbep)-vl+vl0)*cl;
			qdbep=ql+qlo-qlo0;
		}else{
			mv0=sqrt(dv0*dv0+4.0*p[26]*p[26]);
			vl0=-0.5*(dv0+mv0);
			xvar1=(1.0-vl0/p[24]);
			xvar2=(1.0-p[25]);
			xvar3=pow(xvar1,xvar2);
			q0=-p[24]*xvar3/(1.0-p[25]);
			dv=(*Vbep)+dv0;
			mv=sqrt(dv*dv+4.0*p[26]*p[26]);
			vl=0.5*(dv-mv)-dv0;
			xvar1=(1.0-vl/p[24]);
			xvar2=(1.0-p[25]);
			xvar3=pow(xvar1,xvar2);
			qlo=-p[24]*xvar3/(1.0-p[25]);
			xvar1=(1.0-p[14]);
			xvar2=(-p[25]);
			xvar3=pow(xvar1,xvar2);
			qdbep=qlo+xvar3*((*Vbep)-vl+vl0)-q0;
		}
	}
	argi=(*Vbei)/(p[12]*Vtv);
	if(argi>100.0){
		expi=exp(100.0)*(1.0+(argi-100.0));
	}else if(argi<-100.0){
		expi=exp(-100.0)*(1.0+(argi+100.0));
	}else{
		expi=exp(argi);
	}
	Ifi=p[11]*(expi-1.0);
	argi=(*Vbci)/(p[13]*Vtv);
	if(argi>100.0){
		expi=exp(100.0)*(1.0+(argi-100.0));
	}else if(argi<-100.0){
		expi=exp(-100.0)*(1.0+(argi+100.0));
	}else{
		expi=exp(argi);
	}
	Iri=p[11]*p[94]*(expi-1.0);
	q1z=1.0+qdbe*IVER+qdbc*IVEF;
	q1=0.5*(sqrt((q1z-1.0e-4)*(q1z-1.0e-4)+1.0e-8)+q1z-1.0e-4)+1.0e-4;
	q2=Ifi*IIKF+Iri*IIKR;
	if(p[88]<0.5){
		xvar2=1.0/p[89];
		xvar3=pow(q1,xvar2);
		xvar1=(xvar3+4.0*q2);
		xvar4=pow(xvar1,p[89]);
		qb=0.5*(q1+xvar4);
	}else{
		xvar1=(1.0+4.0*q2);
		xvar2=pow(xvar1,p[89]);
		qb=0.5*q1*(1.0+xvar2);
	}
	(*Itzr)=Iri/qb;
	Itzf=Ifi/qb;
	(*Ixzf)=-Itzf;
	(*Itxf)=(*Vrxf);
	(*Ixxf)=(*Vrxf);
	if(p[42]>0.0){
		argi=(*Vbep)/(p[44]*Vtv);
		if(argi>100.0){
			expi=exp(100.0)*(1.0+(argi-100.0));
		}else if(argi<-100.0){
			expi=exp(-100.0)*(1.0+(argi+100.0));
		}else{
			expi=exp(argi);
		}
		argx=(*Vbci)/(p[44]*Vtv);
		if(argx>100.0){
			expx=exp(100.0)*(1.0+(argx-100.0));
		}else if(argx<-100.0){
			expx=exp(-100.0)*(1.0+(argx+100.0));
		}else{
			expx=exp(argx);
		}
		Ifp=p[42]*(p[43]*expi+(1.0-p[43])*expx-1.0);
		q2p=Ifp*IIKP;
		qbp=0.5*(1.0+sqrt(1.0+4.0*q2p));
	}else{
		Ifp=0.0;
		qbp=1.0;
	}
	if(p[32]==1.0){
		argi=(*Vbei)/(p[33]*Vtv);
		if(argi>100.0){
			expi=exp(100.0)*(1.0+(argi-100.0));
		}else if(argi<-100.0){
			expi=exp(-100.0)*(1.0+(argi+100.0));
		}else{
			expi=exp(argi);
		}
		argn=(*Vbei)/(p[35]*Vtv);
		if(argn>100.0){
			expn=exp(100.0)*(1.0+(argn-100.0));
		}else if(argn<-100.0){
			expn=exp(-100.0)*(1.0+(argn+100.0));
		}else{
			expn=exp(argn);
		}
		if(p[98]>0.0){
			argx=(-p[98]-(*Vbei))/(p[99]*Vtv);
			if(argx>100.0){
				expx=exp(100.0)*(1.0+(argx-100.0));
			}else if(argx<-100.0){
				expx=exp(-100.0)*(1.0+(argx+100.0));
			}else{
				expx=exp(argx);
			}
			(*Ibe)=p[31]*(expi-1.0)+p[34]*(expn-1.0)-p[100]*(expx-p[104]);
		}else{
			(*Ibe)=p[31]*(expi-1.0)+p[34]*(expn-1.0);
		}
		(*Ibex)=0.0;
	}else if(p[32]==0.0){
		(*Ibe)=0.0;
		argi=(*Vbex)/(p[33]*Vtv);
		if(argi>100.0){
			expi=exp(100.0)*(1.0+(argi-100.0));
		}else if(argi<-100.0){
			expi=exp(-100.0)*(1.0+(argi+100.0));
		}else{
			expi=exp(argi);
		}
		argn=(*Vbex)/(p[35]*Vtv);
		if(argn>100.0){
			expn=exp(100.0)*(1.0+(argn-100.0));
		}else if(argn<-100.0){
			expn=exp(-100.0)*(1.0+(argn+100.0));
		}else{
			expn=exp(argn);
		}
		if(p[98]>0.0){
			argx=(-p[98]-(*Vbex))/(p[99]*Vtv);
			if(argx>100.0){
				expx=exp(100.0)*(1.0+(argx-100.0));
			}else if(argx<-100.0){
				expx=exp(-100.0)*(1.0+(argx+100.0));
			}else{
				expx=exp(argx);
			}
			(*Ibex)=p[31]*(expi-1.0)+p[34]*(expn-1.0)-p[100]*(expx-p[104]);
		}else{
			(*Ibex)=p[31]*(expi-1.0)+p[34]*(expn-1.0);
		}
	}else{
		argi=(*Vbei)/(p[33]*Vtv);
		if(argi>100.0){
			expi=exp(100.0)*(1.0+(argi-100.0));
		}else if(argi<-100.0){
			expi=exp(-100.0)*(1.0+(argi+100.0));
		}else{
			expi=exp(argi);
		}
		argn=(*Vbei)/(p[35]*Vtv);
		if(argn>100.0){
			expn=exp(100.0)*(1.0+(argn-100.0));
		}else if(argn<-100.0){
			expn=exp(-100.0)*(1.0+(argn+100.0));
		}else{
			expn=exp(argn);
		}
		if(p[98]>0.0){
			argx=(-p[98]-(*Vbei))/(p[99]*Vtv);
			if(argx>100.0){
				expx=exp(100.0)*(1.0+(argx-100.0));
			}else if(argx<-100.0){
				expx=exp(-100.0)*(1.0+(argx+100.0));
			}else{
				expx=exp(argx);
			}
			(*Ibe)=p[32]*(p[31]*(expi-1.0)+p[34]*(expn-1.0)-p[100]*(expx-p[104]));
		}else{
			(*Ibe)=p[32]*(p[31]*(expi-1.0)+p[34]*(expn-1.0));
		}
		argi=(*Vbex)/(p[33]*Vtv);
		if(argi>100.0){
			expi=exp(100.0)*(1.0+(argi-100.0));
		}else if(argi<-100.0){
			expi=exp(-100.0)*(1.0+(argi+100.0));
		}else{
			expi=exp(argi);
		}
		argn=(*Vbex)/(p[35]*Vtv);
		if(argn>100.0){
			expn=exp(100.0)*(1.0+(argn-100.0));
		}else if(argn<-100.0){
			expn=exp(-100.0)*(1.0+(argn+100.0));
		}else{
			expn=exp(argn);
		}
		if(p[98]>0.0){
			argx=(-p[98]-(*Vbex))/(p[99]*Vtv);
			if(argx>100.0){
				expx=exp(100.0)*(1.0+(argx-100.0));
			}else if(argx<-100.0){
				expx=exp(-100.0)*(1.0+(argx+100.0));
			}else{
				expx=exp(argx);
			}
			(*Ibex)=(1.0-p[32])*(p[31]*(expi-1.0)+p[34]*(expn-1.0)-p[100]*(expx-p[104]));
		}else{
			(*Ibex)=(1.0-p[32])*(p[31]*(expi-1.0)+p[34]*(expn-1.0));
		}
	}
	argi=(*Vbci)/(p[37]*Vtv);
	if(argi>100.0){
		expi=exp(100.0)*(1.0+(argi-100.0));
	}else if(argi<-100.0){
		expi=exp(-100.0)*(1.0+(argi+100.0));
	}else{
		expi=exp(argi);
	}
	argn=(*Vbci)/(p[39]*Vtv);
	if(argn>100.0){
		expn=exp(100.0)*(1.0+(argn-100.0));
	}else if(argn<-100.0){
		expn=exp(-100.0)*(1.0+(argn+100.0));
	}else{
		expn=exp(argn);
	}
	Ibcj=p[36]*(expi-1.0)+p[38]*(expn-1.0);
	if((p[45]>0.0)||(p[46]>0.0)){
		argi=(*Vbep)/(p[37]*Vtv);
		if(argi>100.0){
			expi=exp(100.0)*(1.0+(argi-100.0));
		}else if(argi<-100.0){
			expi=exp(-100.0)*(1.0+(argi+100.0));
		}else{
			expi=exp(argi);
		}
		argn=(*Vbep)/(p[39]*Vtv);
		if(argn>100.0){
			expn=exp(100.0)*(1.0+(argn-100.0));
		}else if(argn<-100.0){
			expn=exp(-100.0)*(1.0+(argn+100.0));
		}else{
			expn=exp(argn);
		}
		(*Ibep)=p[45]*(expi-1.0)+p[46]*(expn-1.0);
	}else{
		(*Ibep)=0.0;
	}
	if(p[40]>0.0){
		vl=0.5*(sqrt((p[24]-(*Vbci))*(p[24]-(*Vbci))+0.01)+(p[24]-(*Vbci)));
		xvar2=(p[25]-1.0);
		xvar3=pow(vl,xvar2);
		xvar1=-p[41]*xvar3;
		if(xvar1>100.0){
			xvar4=exp(100.0)*(1.0+(xvar1-100.0));
		}else if(xvar1<-100.0){
			xvar4=exp(-100.0)*(1.0+(xvar1+100.0));
		}else{
			xvar4=exp(xvar1);
		}
		avalf=p[40]*vl*xvar4;
		Igc=((*Itxf)-(*Itzr)-Ibcj)*avalf;
	}else{
		Igc=0.0;
	}
	(*Ibc)=Ibcj-Igc;
	if(p[1]>0.0){
		(*Ircx)=(*Vrcx)/p[1];
	}else{
		(*Ircx)=0.0;
	}
	argi=(*Vbci)/Vtv;
	if(argi>100.0){
		expi=exp(100.0)*(1.0+(argi-100.0));
	}else if(argi<-100.0){
		expi=exp(-100.0)*(1.0+(argi+100.0));
	}else{
		expi=exp(argi);
	}
	argx=(*Vbcx)/Vtv;
	if(argx>100.0){
		expx=exp(100.0)*(1.0+(argx-100.0));
	}else if(argx<-100.0){
		expx=exp(-100.0)*(1.0+(argx+100.0));
	}else{
		expx=exp(argx);
	}
	Kbci=sqrt(1.0+p[4]*expi);
	Kbcx=sqrt(1.0+p[4]*expx);
	if(p[2]>0.0){
		rKp1=(Kbci+1.0)/(Kbcx+1.0);
		xvar1=log(rKp1);
		Iohm=((*Vrci)+Vtv*(Kbci-Kbcx-xvar1))/p[2];
		derf=IVO*p[2]*Iohm/(1.0+0.5*IVO*IHRCF*sqrt((*Vrci)*(*Vrci)+0.01));
		(*Irci)=Iohm/sqrt(1.0+derf*derf);
	}else{
		(*Irci)=0.0;
	}
	if(p[6]>0.0){
		(*Irbx)=(*Vrbx)/p[6];
	}else{
		(*Irbx)=0.0;
	}
	if(p[7]>0.0){
		(*Irbi)=(*Vrbi)*qb/p[7];
	}else{
		(*Irbi)=0.0;
	}
	if(p[8]>0.0){
		(*Ire)=(*Vre)/p[8];
	}else{
		(*Ire)=0.0;
	}
	if(p[10]>0.0){
		(*Irbp)=(*Vrbp)*qbp/p[10];
	}else{
		(*Irbp)=0.0;
	}
	if(Ifi>0.0){
		sgIf=1.0;
	}else{
		sgIf=0.0;
	}
	rIf=Ifi*sgIf*IITF;
	mIf=rIf/(rIf+1.0);
	xvar1=(*Vbci)*IVTF/1.44;
	if(xvar1>100.0){
		xvar2=exp(100.0)*(1.0+(xvar1-100.0));
	}else if(xvar1<-100.0){
		xvar2=exp(-100.0)*(1.0+(xvar1+100.0));
	}else{
		xvar2=exp(xvar1);
	}
	tff=p[56]*(1.0+p[57]*q1)*(1.0+p[58]*xvar2*(slTF+mIf*mIf)*sgIf);
	(*Qbe)=p[16]*qdbe*p[32]+tff*Ifi/qb;
	(*Qbex)=p[16]*qdbex*(1.0-p[32]);
	(*Qbc)=p[21]*qdbc+p[61]*Iri+p[22]*Kbci;
	(*Qbcx)=p[22]*Kbcx;
	(*Qbep)=p[23]*qdbep+p[61]*Ifp;
	(*Qbeo)=(*Vbe)*p[15];
	(*Qbco)=(*Vbc)*p[20];
	(*Flxf)=LEP*(*Ixxf);
	(*Qcxf)=CEP*(*Vcxf);

/*	Scale outputs */
	if(*SCALE!=1.0){
		*Ibe=(*SCALE)*(*Ibe);
		*Ibex=(*SCALE)*(*Ibex);
		*Itxf=(*SCALE)*(*Itxf);
		*Itzr=(*SCALE)*(*Itzr);
		*Ibc=(*SCALE)*(*Ibc);
		*Ibep=(*SCALE)*(*Ibep);
		*Ircx=(*SCALE)*(*Ircx);
		*Irci=(*SCALE)*(*Irci);
		*Irbx=(*SCALE)*(*Irbx);
		*Irbi=(*SCALE)*(*Irbi);
		*Ire=(*SCALE)*(*Ire);
		*Irbp=(*SCALE)*(*Irbp);
		*Qbe=(*SCALE)*(*Qbe);
		*Qbex=(*SCALE)*(*Qbex);
		*Qbc=(*SCALE)*(*Qbc);
		*Qbcx=(*SCALE)*(*Qbcx);
		*Qbep=(*SCALE)*(*Qbep);
		*Qbeo=(*SCALE)*(*Qbeo);
		*Qbco=(*SCALE)*(*Qbco);
		*Ixzf=(*SCALE)*(*Ixzf);
		*Ixxf=(*SCALE)*(*Ixxf);
		*Qcxf=(*SCALE)*(*Qcxf);
		*Flxf=(*SCALE)*(*Flxf);
	}
	return(0);
}
