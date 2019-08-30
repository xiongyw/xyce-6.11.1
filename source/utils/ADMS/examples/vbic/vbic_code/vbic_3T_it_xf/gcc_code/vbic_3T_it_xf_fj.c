
#include <stdio.h>
#include <math.h>

int vbic_3T_it_xf_fj(p
	,Vbei,Vbex,Vbci,Vbep,Vrxf,Vrcx
	,Vbcx,Vrci,Vrbx,Vrbi,Vre,Vrbp,Vbe
	,Vbc,Vcxf,Ibe,Ibe_Vbei,Ibex,Ibex_Vbex,Itxf
	,Itxf_Vrxf,Itzr,Itzr_Vbci,Itzr_Vbei,Ibc,Ibc_Vbci,Ibc_Vrxf
	,Ibc_Vbei,Ibep,Ibep_Vbep,Ircx,Ircx_Vrcx,Irci,Irci_Vrci
	,Irci_Vbci,Irci_Vbcx,Irbx,Irbx_Vrbx,Irbi,Irbi_Vrbi,Irbi_Vbei
	,Irbi_Vbci,Ire,Ire_Vre,Irbp,Irbp_Vrbp,Irbp_Vbep,Irbp_Vbci
	,Qbe,Qbe_Vbei,Qbe_Vbci,Qbex,Qbex_Vbex,Qbc,Qbc_Vbci
	,Qbcx,Qbcx_Vbcx,Qbep,Qbep_Vbep,Qbep_Vbci,Qbeo,Qbeo_Vbe
	,Qbco,Qbco_Vbc,Ixzf,Ixzf_Vbei,Ixzf_Vbci,Ixxf,Ixxf_Vrxf
	,Qcxf,Qcxf_Vcxf,Flxf,Flxf_Vrxf,SCALE)
double *p
	,*Vbei,*Vbex,*Vbci,*Vbep,*Vrxf,*Vrcx
	,*Vbcx,*Vrci,*Vrbx,*Vrbi,*Vre,*Vrbp,*Vbe
	,*Vbc,*Vcxf,*Ibe,*Ibe_Vbei,*Ibex,*Ibex_Vbex,*Itxf
	,*Itxf_Vrxf,*Itzr,*Itzr_Vbci,*Itzr_Vbei,*Ibc,*Ibc_Vbci,*Ibc_Vrxf
	,*Ibc_Vbei,*Ibep,*Ibep_Vbep,*Ircx,*Ircx_Vrcx,*Irci,*Irci_Vrci
	,*Irci_Vbci,*Irci_Vbcx,*Irbx,*Irbx_Vrbx,*Irbi,*Irbi_Vrbi,*Irbi_Vbei
	,*Irbi_Vbci,*Ire,*Ire_Vre,*Irbp,*Irbp_Vrbp,*Irbp_Vbep,*Irbp_Vbci
	,*Qbe,*Qbe_Vbei,*Qbe_Vbci,*Qbex,*Qbex_Vbex,*Qbc,*Qbc_Vbci
	,*Qbcx,*Qbcx_Vbcx,*Qbep,*Qbep_Vbep,*Qbep_Vbci,*Qbeo,*Qbeo_Vbe
	,*Qbco,*Qbco_Vbc,*Ixzf,*Ixzf_Vbei,*Ixzf_Vbci,*Ixxf,*Ixxf_Vrxf
	,*Qcxf,*Qcxf_Vcxf,*Flxf,*Flxf_Vrxf,*SCALE;
{
double	Vtv,IVEF,IVER,IIKF,IIKR,IIKP,IVO;
double	IHRCF,IVTF,IITF,slTF,LEP,CEP,dv0;
double	dvh,dvh_Vbei,xvar1,xvar2,pwq,qlo,qlo_Vbei;
double	qhi,qhi_dvh,qhi_Vbei,xvar1_Vbei,xvar3,xvar3_xvar1,xvar3_Vbei;
double	qlo_xvar3,qdbe,qdbe_qlo,qdbe_Vbei,qdbe_qhi,mv0,vl0;
double	q0,dv,dv_Vbei,mv,mv_dv,mv_Vbei,vl;
double	vl_dv,vl_Vbei,vl_mv,xvar1_vl,qdbe_vl,dvh_Vbex,qlo_Vbex;
double	qhi_Vbex,xvar1_Vbex,xvar3_Vbex,qdbex,qdbex_qlo,qdbex_Vbex,qdbex_qhi;
double	dv_Vbex,mv_Vbex,vl_Vbex,qdbex_vl,dvh_Vbci,qlo_Vbci,qhi_Vbci;
double	xvar1_Vbci,xvar3_Vbci,qdbc,qdbc_qlo,qdbc_Vbci,qdbc_qhi,vn0;
double	vnl0,qlo0,vn,vn_Vbci,vnl,vnl_vn,vnl_Vbci;
double	vl_vnl,vl_Vbci,sel,sel_vnl,sel_Vbci,crt,cmx;
double	cl,cl_sel,cl_Vbci,ql,ql_Vbci,ql_vl,ql_cl;
double	qdbc_ql,dv_Vbci,mv_Vbci,qdbc_vl,dvh_Vbep,qlo_Vbep,qhi_Vbep;
double	xvar1_Vbep,xvar3_Vbep,qdbep,qdbep_qlo,qdbep_Vbep,qdbep_qhi,vn_Vbep;
double	vnl_Vbep,vl_Vbep,sel_Vbep,cl_Vbep,ql_Vbep,qdbep_ql,dv_Vbep;
double	mv_Vbep,qdbep_vl,argi,argi_Vbei,expi,expi_argi,expi_Vbei;
double	Ifi,Ifi_expi,Ifi_Vbei,argi_Vbci,expi_Vbci,Iri,Iri_expi;
double	Iri_Vbci,q1z,q1z_qdbe,q1z_Vbei,q1z_qdbc,q1z_Vbci,q1;
double	q1_q1z,q1_Vbei,q1_Vbci,q2,q2_Ifi,q2_Vbei,q2_Iri;
double	q2_Vbci,xvar3_q1,xvar1_xvar3,xvar1_q2,xvar4,xvar4_xvar1,xvar4_Vbei;
double	xvar4_Vbci,qb,qb_q1,qb_Vbei,qb_Vbci,qb_xvar4,xvar2_xvar1;
double	xvar2_Vbei,xvar2_Vbci,qb_xvar2,Itzr_Iri,Itzr_qb,Itzf,Itzf_Ifi;
double	Itzf_Vbei,Itzf_qb,Itzf_Vbci,Ixzf_Itzf,argi_Vbep,expi_Vbep,argx;
double	argx_Vbci,expx,expx_argx,expx_Vbci,Ifp,Ifp_expi,Ifp_Vbep;
double	Ifp_expx,Ifp_Vbci,q2p,q2p_Ifp,q2p_Vbep,q2p_Vbci,qbp;
double	qbp_q2p,qbp_Vbep,qbp_Vbci,argn,argn_Vbei,expn,expn_argn;
double	expn_Vbei,argx_Vbei,expx_Vbei,Ibe_expi,Ibe_expn,Ibe_expx,argi_Vbex;
double	expi_Vbex,argn_Vbex,expn_Vbex,argx_Vbex,expx_Vbex,Ibex_expi,Ibex_expn;
double	Ibex_expx,argn_Vbci,expn_Vbci,Ibcj,Ibcj_expi,Ibcj_Vbci,Ibcj_expn;
double	argn_Vbep,expn_Vbep,Ibep_expi,Ibep_expn,xvar3_vl,avalf,avalf_vl;
double	avalf_Vbci,avalf_xvar4,Igc,Igc_Itxf,Igc_Vrxf,Igc_Itzr,Igc_Vbci;
double	Igc_Vbei,Igc_Ibcj,Igc_avalf,Ibc_Ibcj,Ibc_Igc,argx_Vbcx,expx_Vbcx;
double	Kbci,Kbci_expi,Kbci_Vbci,Kbcx,Kbcx_expx,Kbcx_Vbcx,rKp1;
double	rKp1_Kbci,rKp1_Vbci,rKp1_Kbcx,rKp1_Vbcx,xvar1_rKp1,xvar1_Vbcx,Iohm;
double	Iohm_Vrci,Iohm_Kbci,Iohm_Vbci,Iohm_Kbcx,Iohm_Vbcx,Iohm_xvar1,derf;
double	derf_Iohm,derf_Vrci,derf_Vbci,derf_Vbcx,Irci_Iohm,Irci_derf,Irbi_qb;
double	Irbp_qbp,sgIf,rIf,rIf_Ifi,rIf_Vbei,mIf,mIf_rIf;
double	mIf_Vbei,tff,tff_q1,tff_Vbei,tff_Vbci,tff_xvar2,tff_mIf;
double	Qbe_qdbe,Qbe_tff,Qbe_Ifi,Qbe_qb,Qbex_qdbex,Qbc_qdbc,Qbc_Iri;
double	Qbc_Kbci,Qbcx_Kbcx,Qbep_qdbep,Qbep_Ifp,Flxf_Ixxf;

/*	Function and derivative code */

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
		dvh_Vbei=1.0;
		if(dvh>0.0){
			xvar1=(1.0-p[14]);
			xvar2=(-1.0-p[18]);
			pwq=pow(xvar1,xvar2);
			qlo=p[17]*(1.0-pwq*(1.0-p[14])*(1.0-p[14]))/(1.0-p[18]);
			qlo_Vbei=0.0;
			qhi=dvh*(1.0-p[14]+0.5*p[18]*dvh/p[17])*pwq;
			qhi_dvh=(0.5*dvh*p[18]/p[17]-p[14]+1.0)*pwq+0.5*dvh*p[18]*pwq/p[17];
			qhi_Vbei=qhi_dvh*dvh_Vbei;
		}else{
			xvar1=(1.0-(*Vbei)/p[17]);
			xvar1_Vbei=-1.0/p[17];
			xvar2=(1.0-p[18]);
			xvar3=pow(xvar1,xvar2);
			xvar3_xvar1=xvar3*xvar2/xvar1;
			xvar3_Vbei=xvar3_xvar1*xvar1_Vbei;
			qlo=p[17]*(1.0-xvar3)/(1.0-p[18]);
			qlo_xvar3=-p[17]/(1.0-p[18]);
			qlo_Vbei=qlo_xvar3*xvar3_Vbei;
			qhi=0.0;
			qhi_Vbei=0.0;
		}
		qdbe=qlo+qhi;
		qdbe_qlo=1.0;
		qdbe_qhi=1.0;
		qdbe_Vbei=qdbe_qlo*qlo_Vbei;
		qdbe_Vbei=qdbe_Vbei+qdbe_qhi*qhi_Vbei;
	}else{
		mv0=sqrt(dv0*dv0+4.0*p[19]*p[19]);
		vl0=-0.5*(dv0+mv0);
		xvar1=(1.0-vl0/p[17]);
		xvar2=(1.0-p[18]);
		xvar3=pow(xvar1,xvar2);
		q0=-p[17]*xvar3/(1.0-p[18]);
		dv=(*Vbei)+dv0;
		dv_Vbei=1.0;
		mv=sqrt(dv*dv+4.0*p[19]*p[19]);
		mv_dv=dv/sqrt((dv*dv)+4.0*(p[19]*p[19]));
		mv_Vbei=mv_dv*dv_Vbei;
		vl=0.5*(dv-mv)-dv0;
		vl_dv=0.5;
		vl_mv=-0.5;
		vl_Vbei=vl_dv*dv_Vbei;
		vl_Vbei=vl_Vbei+vl_mv*mv_Vbei;
		xvar1=(1.0-vl/p[17]);
		xvar1_vl=-1.0/p[17];
		xvar1_Vbei=xvar1_vl*vl_Vbei;
		xvar2=(1.0-p[18]);
		xvar3=pow(xvar1,xvar2);
		xvar3_xvar1=xvar3*xvar2/xvar1;
		xvar3_Vbei=xvar3_xvar1*xvar1_Vbei;
		qlo=-p[17]*xvar3/(1.0-p[18]);
		qlo_xvar3=-p[17]/(1.0-p[18]);
		qlo_Vbei=qlo_xvar3*xvar3_Vbei;
		xvar1=(1.0-p[14]);
		xvar2=(-p[18]);
		xvar3=pow(xvar1,xvar2);
		qdbe=qlo+xvar3*((*Vbei)-vl+vl0)-q0;
		qdbe_qlo=1.0;
		qdbe_Vbei=xvar3;
		qdbe_vl=-xvar3;
		qdbe_Vbei=qdbe_Vbei+qdbe_qlo*qlo_Vbei;
		qdbe_Vbei=qdbe_Vbei+qdbe_vl*vl_Vbei;
	}
	dv0=-p[17]*p[14];
	if(p[19]<=0.0){
		dvh=(*Vbex)+dv0;
		dvh_Vbex=1.0;
		if(dvh>0.0){
			xvar1=(1.0-p[14]);
			xvar2=(-1.0-p[18]);
			pwq=pow(xvar1,xvar2);
			qlo=p[17]*(1.0-pwq*(1.0-p[14])*(1.0-p[14]))/(1.0-p[18]);
			qlo_Vbex=0.0;
			qhi=dvh*(1.0-p[14]+0.5*p[18]*dvh/p[17])*pwq;
			qhi_dvh=(0.5*dvh*p[18]/p[17]-p[14]+1.0)*pwq+0.5*dvh*p[18]*pwq/p[17];
			qhi_Vbex=qhi_dvh*dvh_Vbex;
		}else{
			xvar1=(1.0-(*Vbex)/p[17]);
			xvar1_Vbex=-1.0/p[17];
			xvar2=(1.0-p[18]);
			xvar3=pow(xvar1,xvar2);
			xvar3_xvar1=xvar3*xvar2/xvar1;
			xvar3_Vbex=xvar3_xvar1*xvar1_Vbex;
			qlo=p[17]*(1.0-xvar3)/(1.0-p[18]);
			qlo_xvar3=-p[17]/(1.0-p[18]);
			qlo_Vbex=qlo_xvar3*xvar3_Vbex;
			qhi=0.0;
			qhi_Vbex=0.0;
		}
		qdbex=qlo+qhi;
		qdbex_qlo=1.0;
		qdbex_qhi=1.0;
		qdbex_Vbex=qdbex_qlo*qlo_Vbex;
		qdbex_Vbex=qdbex_Vbex+qdbex_qhi*qhi_Vbex;
	}else{
		mv0=sqrt(dv0*dv0+4.0*p[19]*p[19]);
		vl0=-0.5*(dv0+mv0);
		xvar1=(1.0-vl0/p[17]);
		xvar2=(1.0-p[18]);
		xvar3=pow(xvar1,xvar2);
		q0=-p[17]*xvar3/(1.0-p[18]);
		dv=(*Vbex)+dv0;
		dv_Vbex=1.0;
		mv=sqrt(dv*dv+4.0*p[19]*p[19]);
		mv_dv=dv/sqrt((dv*dv)+4.0*(p[19]*p[19]));
		mv_Vbex=mv_dv*dv_Vbex;
		vl=0.5*(dv-mv)-dv0;
		vl_dv=0.5;
		vl_mv=-0.5;
		vl_Vbex=vl_dv*dv_Vbex;
		vl_Vbex=vl_Vbex+vl_mv*mv_Vbex;
		xvar1=(1.0-vl/p[17]);
		xvar1_vl=-1.0/p[17];
		xvar1_Vbex=xvar1_vl*vl_Vbex;
		xvar2=(1.0-p[18]);
		xvar3=pow(xvar1,xvar2);
		xvar3_xvar1=xvar3*xvar2/xvar1;
		xvar3_Vbex=xvar3_xvar1*xvar1_Vbex;
		qlo=-p[17]*xvar3/(1.0-p[18]);
		qlo_xvar3=-p[17]/(1.0-p[18]);
		qlo_Vbex=qlo_xvar3*xvar3_Vbex;
		xvar1=(1.0-p[14]);
		xvar2=(-p[18]);
		xvar3=pow(xvar1,xvar2);
		qdbex=qlo+xvar3*((*Vbex)-vl+vl0)-q0;
		qdbex_qlo=1.0;
		qdbex_Vbex=xvar3;
		qdbex_vl=-xvar3;
		qdbex_Vbex=qdbex_Vbex+qdbex_qlo*qlo_Vbex;
		qdbex_Vbex=qdbex_Vbex+qdbex_vl*vl_Vbex;
	}
	dv0=-p[24]*p[14];
	if(p[26]<=0.0){
		dvh=(*Vbci)+dv0;
		dvh_Vbci=1.0;
		if(dvh>0.0){
			xvar1=(1.0-p[14]);
			xvar2=(-1.0-p[25]);
			pwq=pow(xvar1,xvar2);
			qlo=p[24]*(1.0-pwq*(1.0-p[14])*(1.0-p[14]))/(1.0-p[25]);
			qlo_Vbci=0.0;
			qhi=dvh*(1.0-p[14]+0.5*p[25]*dvh/p[24])*pwq;
			qhi_dvh=(0.5*dvh*p[25]/p[24]-p[14]+1.0)*pwq+0.5*dvh*p[25]*pwq/p[24];
			qhi_Vbci=qhi_dvh*dvh_Vbci;
		}else{
			if((p[85]>0.0)&&((*Vbci)<-p[85])){
				xvar1=(1.0+p[85]/p[24]);
				xvar2=(1.0-p[25]);
				xvar3=pow(xvar1,xvar2);
				qlo=p[24]*(1.0-xvar3*(1.0-((1.0-p[25])*((*Vbci)+p[85]))/(p[24]+p[85])))/(1.0-p[25]);
				qlo_Vbci=p[24]*xvar3/(p[85]+p[24]);
			}else{
				xvar1=(1.0-(*Vbci)/p[24]);
				xvar1_Vbci=-1.0/p[24];
				xvar2=(1.0-p[25]);
				xvar3=pow(xvar1,xvar2);
				xvar3_xvar1=xvar3*xvar2/xvar1;
				xvar3_Vbci=xvar3_xvar1*xvar1_Vbci;
				qlo=p[24]*(1.0-xvar3)/(1.0-p[25]);
				qlo_xvar3=-p[24]/(1.0-p[25]);
				qlo_Vbci=qlo_xvar3*xvar3_Vbci;
			}
			qhi=0.0;
			qhi_Vbci=0.0;
		}
		qdbc=qlo+qhi;
		qdbc_qlo=1.0;
		qdbc_qhi=1.0;
		qdbc_Vbci=qdbc_qlo*qlo_Vbci;
		qdbc_Vbci=qdbc_Vbci+qdbc_qhi*qhi_Vbci;
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
			vn_Vbci=2.0/(p[85]-dv0);
			vnl=2.0*vn/(sqrt((vn-1.0)*(vn-1.0)+4.0*p[26]*p[26])+sqrt((vn+1.0)*(vn+1.0)+4.0*p[86]*p[86]));
			vnl_vn=2.0/(sqrt(((vn+1.0)*(vn+1.0))+4.0*(p[86]*p[86]))+sqrt(((vn-1.0)*(vn-1.0))+4.0*(p[26]*p[26])))-2.0*vn*((vn+1.0)/sqrt(((vn+1.0)*(vn+1.0))+4.0*(p[86]*p[86]))+(vn-1.0)/sqrt(((vn-1.0)*(vn-1.0))+4.0*(p[26]*p[26])))/((sqrt(((vn+1.0)*(vn+1.0))+4.0*(p[86]*p[86]))+sqrt(((vn-1.0)*(vn-1.0))+4.0*(p[26]*p[26])))*(sqrt(((vn+1.0)*(vn+1.0))+4.0*(p[86]*p[86]))+sqrt(((vn-1.0)*(vn-1.0))+4.0*(p[26]*p[26]))));
			vnl_Vbci=vnl_vn*vn_Vbci;
			vl=0.5*(vnl*(p[85]-dv0)-p[85]-dv0);
			vl_vnl=0.5*(p[85]-dv0);
			vl_Vbci=vl_vnl*vnl_Vbci;
			xvar1=(1.0-vl/p[24]);
			xvar1_vl=-1.0/p[24];
			xvar1_Vbci=xvar1_vl*vl_Vbci;
			xvar2=(1.0-p[25]);
			xvar3=pow(xvar1,xvar2);
			xvar3_xvar1=xvar3*xvar2/xvar1;
			xvar3_Vbci=xvar3_xvar1*xvar1_Vbci;
			qlo=p[24]*(1.0-xvar3)/(1.0-p[25]);
			qlo_xvar3=-p[24]/(1.0-p[25]);
			qlo_Vbci=qlo_xvar3*xvar3_Vbci;
			sel=0.5*(vnl+1.0);
			sel_vnl=0.5;
			sel_Vbci=sel_vnl*vnl_Vbci;
			xvar1=(1.0+p[85]/p[24]);
			xvar2=(-p[25]);
			crt=pow(xvar1,xvar2);
			xvar1=(1.0+dv0/p[24]);
			xvar2=(-p[25]);
			cmx=pow(xvar1,xvar2);
			cl=(1.0-sel)*crt+sel*cmx;
			cl_sel=cmx-crt;
			cl_Vbci=cl_sel*sel_Vbci;
			ql=((*Vbci)-vl+vl0)*cl;
			ql_Vbci=cl;
			ql_vl=-cl;
			ql_cl=vl0-vl+(*Vbci);
			ql_Vbci=ql_Vbci+ql_vl*vl_Vbci;
			ql_Vbci=ql_Vbci+ql_cl*cl_Vbci;
			qdbc=ql+qlo-qlo0;
			qdbc_ql=1.0;
			qdbc_qlo=1.0;
			qdbc_Vbci=qdbc_ql*ql_Vbci;
			qdbc_Vbci=qdbc_Vbci+qdbc_qlo*qlo_Vbci;
		}else{
			mv0=sqrt(dv0*dv0+4.0*p[26]*p[26]);
			vl0=-0.5*(dv0+mv0);
			xvar1=(1.0-vl0/p[24]);
			xvar2=(1.0-p[25]);
			xvar3=pow(xvar1,xvar2);
			q0=-p[24]*xvar3/(1.0-p[25]);
			dv=(*Vbci)+dv0;
			dv_Vbci=1.0;
			mv=sqrt(dv*dv+4.0*p[26]*p[26]);
			mv_dv=dv/sqrt((dv*dv)+4.0*(p[26]*p[26]));
			mv_Vbci=mv_dv*dv_Vbci;
			vl=0.5*(dv-mv)-dv0;
			vl_dv=0.5;
			vl_mv=-0.5;
			vl_Vbci=vl_dv*dv_Vbci;
			vl_Vbci=vl_Vbci+vl_mv*mv_Vbci;
			xvar1=(1.0-vl/p[24]);
			xvar1_vl=-1.0/p[24];
			xvar1_Vbci=xvar1_vl*vl_Vbci;
			xvar2=(1.0-p[25]);
			xvar3=pow(xvar1,xvar2);
			xvar3_xvar1=xvar3*xvar2/xvar1;
			xvar3_Vbci=xvar3_xvar1*xvar1_Vbci;
			qlo=-p[24]*xvar3/(1.0-p[25]);
			qlo_xvar3=-p[24]/(1.0-p[25]);
			qlo_Vbci=qlo_xvar3*xvar3_Vbci;
			xvar1=(1.0-p[14]);
			xvar2=(-p[25]);
			xvar3=pow(xvar1,xvar2);
			qdbc=qlo+xvar3*((*Vbci)-vl+vl0)-q0;
			qdbc_qlo=1.0;
			qdbc_Vbci=xvar3;
			qdbc_vl=-xvar3;
			qdbc_Vbci=qdbc_Vbci+qdbc_qlo*qlo_Vbci;
			qdbc_Vbci=qdbc_Vbci+qdbc_vl*vl_Vbci;
		}
	}
	dv0=-p[24]*p[14];
	if(p[26]<=0.0){
		dvh=(*Vbep)+dv0;
		dvh_Vbep=1.0;
		if(dvh>0.0){
			xvar1=(1.0-p[14]);
			xvar2=(-1.0-p[25]);
			pwq=pow(xvar1,xvar2);
			qlo=p[24]*(1.0-pwq*(1.0-p[14])*(1.0-p[14]))/(1.0-p[25]);
			qlo_Vbep=0.0;
			qhi=dvh*(1.0-p[14]+0.5*p[25]*dvh/p[24])*pwq;
			qhi_dvh=(0.5*dvh*p[25]/p[24]-p[14]+1.0)*pwq+0.5*dvh*p[25]*pwq/p[24];
			qhi_Vbep=qhi_dvh*dvh_Vbep;
		}else{
			if((p[85]>0.0)&&((*Vbep)<-p[85])){
				xvar1=(1.0+p[85]/p[24]);
				xvar2=(1.0-p[25]);
				xvar3=pow(xvar1,xvar2);
				qlo=p[24]*(1.0-xvar3*(1.0-((1.0-p[25])*((*Vbep)+p[85]))/(p[24]+p[85])))/(1.0-p[25]);
				qlo_Vbep=p[24]*xvar3/(p[85]+p[24]);
			}else{
				xvar1=(1.0-(*Vbep)/p[24]);
				xvar1_Vbep=-1.0/p[24];
				xvar2=(1.0-p[25]);
				xvar3=pow(xvar1,xvar2);
				xvar3_xvar1=xvar3*xvar2/xvar1;
				xvar3_Vbep=xvar3_xvar1*xvar1_Vbep;
				qlo=p[24]*(1.0-xvar3)/(1.0-p[25]);
				qlo_xvar3=-p[24]/(1.0-p[25]);
				qlo_Vbep=qlo_xvar3*xvar3_Vbep;
			}
			qhi=0.0;
			qhi_Vbep=0.0;
		}
		qdbep=qlo+qhi;
		qdbep_qlo=1.0;
		qdbep_qhi=1.0;
		qdbep_Vbep=qdbep_qlo*qlo_Vbep;
		qdbep_Vbep=qdbep_Vbep+qdbep_qhi*qhi_Vbep;
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
			vn_Vbep=2.0/(p[85]-dv0);
			vnl=2.0*vn/(sqrt((vn-1.0)*(vn-1.0)+4.0*p[26]*p[26])+sqrt((vn+1.0)*(vn+1.0)+4.0*p[86]*p[86]));
			vnl_vn=2.0/(sqrt(((vn+1.0)*(vn+1.0))+4.0*(p[86]*p[86]))+sqrt(((vn-1.0)*(vn-1.0))+4.0*(p[26]*p[26])))-2.0*vn*((vn+1.0)/sqrt(((vn+1.0)*(vn+1.0))+4.0*(p[86]*p[86]))+(vn-1.0)/sqrt(((vn-1.0)*(vn-1.0))+4.0*(p[26]*p[26])))/((sqrt(((vn+1.0)*(vn+1.0))+4.0*(p[86]*p[86]))+sqrt(((vn-1.0)*(vn-1.0))+4.0*(p[26]*p[26])))*(sqrt(((vn+1.0)*(vn+1.0))+4.0*(p[86]*p[86]))+sqrt(((vn-1.0)*(vn-1.0))+4.0*(p[26]*p[26]))));
			vnl_Vbep=vnl_vn*vn_Vbep;
			vl=0.5*(vnl*(p[85]-dv0)-p[85]-dv0);
			vl_vnl=0.5*(p[85]-dv0);
			vl_Vbep=vl_vnl*vnl_Vbep;
			xvar1=(1.0-vl/p[24]);
			xvar1_vl=-1.0/p[24];
			xvar1_Vbep=xvar1_vl*vl_Vbep;
			xvar2=(1.0-p[25]);
			xvar3=pow(xvar1,xvar2);
			xvar3_xvar1=xvar3*xvar2/xvar1;
			xvar3_Vbep=xvar3_xvar1*xvar1_Vbep;
			qlo=p[24]*(1.0-xvar3)/(1.0-p[25]);
			qlo_xvar3=-p[24]/(1.0-p[25]);
			qlo_Vbep=qlo_xvar3*xvar3_Vbep;
			sel=0.5*(vnl+1.0);
			sel_vnl=0.5;
			sel_Vbep=sel_vnl*vnl_Vbep;
			xvar1=(1.0+p[85]/p[24]);
			xvar2=(-p[25]);
			crt=pow(xvar1,xvar2);
			xvar1=(1.0+dv0/p[24]);
			xvar2=(-p[25]);
			cmx=pow(xvar1,xvar2);
			cl=(1.0-sel)*crt+sel*cmx;
			cl_sel=cmx-crt;
			cl_Vbep=cl_sel*sel_Vbep;
			ql=((*Vbep)-vl+vl0)*cl;
			ql_Vbep=cl;
			ql_vl=-cl;
			ql_cl=vl0-vl+(*Vbep);
			ql_Vbep=ql_Vbep+ql_vl*vl_Vbep;
			ql_Vbep=ql_Vbep+ql_cl*cl_Vbep;
			qdbep=ql+qlo-qlo0;
			qdbep_ql=1.0;
			qdbep_qlo=1.0;
			qdbep_Vbep=qdbep_ql*ql_Vbep;
			qdbep_Vbep=qdbep_Vbep+qdbep_qlo*qlo_Vbep;
		}else{
			mv0=sqrt(dv0*dv0+4.0*p[26]*p[26]);
			vl0=-0.5*(dv0+mv0);
			xvar1=(1.0-vl0/p[24]);
			xvar2=(1.0-p[25]);
			xvar3=pow(xvar1,xvar2);
			q0=-p[24]*xvar3/(1.0-p[25]);
			dv=(*Vbep)+dv0;
			dv_Vbep=1.0;
			mv=sqrt(dv*dv+4.0*p[26]*p[26]);
			mv_dv=dv/sqrt((dv*dv)+4.0*(p[26]*p[26]));
			mv_Vbep=mv_dv*dv_Vbep;
			vl=0.5*(dv-mv)-dv0;
			vl_dv=0.5;
			vl_mv=-0.5;
			vl_Vbep=vl_dv*dv_Vbep;
			vl_Vbep=vl_Vbep+vl_mv*mv_Vbep;
			xvar1=(1.0-vl/p[24]);
			xvar1_vl=-1.0/p[24];
			xvar1_Vbep=xvar1_vl*vl_Vbep;
			xvar2=(1.0-p[25]);
			xvar3=pow(xvar1,xvar2);
			xvar3_xvar1=xvar3*xvar2/xvar1;
			xvar3_Vbep=xvar3_xvar1*xvar1_Vbep;
			qlo=-p[24]*xvar3/(1.0-p[25]);
			qlo_xvar3=-p[24]/(1.0-p[25]);
			qlo_Vbep=qlo_xvar3*xvar3_Vbep;
			xvar1=(1.0-p[14]);
			xvar2=(-p[25]);
			xvar3=pow(xvar1,xvar2);
			qdbep=qlo+xvar3*((*Vbep)-vl+vl0)-q0;
			qdbep_qlo=1.0;
			qdbep_Vbep=xvar3;
			qdbep_vl=-xvar3;
			qdbep_Vbep=qdbep_Vbep+qdbep_qlo*qlo_Vbep;
			qdbep_Vbep=qdbep_Vbep+qdbep_vl*vl_Vbep;
		}
	}
	argi=(*Vbei)/(p[12]*Vtv);
	argi_Vbei=1.0/(p[12]*Vtv);
	expi=exp(argi);
	expi_argi=expi;
	expi_Vbei=expi_argi*argi_Vbei;
	Ifi=p[11]*(expi-1.0);
	Ifi_expi=p[11];
	Ifi_Vbei=Ifi_expi*expi_Vbei;
	argi=(*Vbci)/(p[13]*Vtv);
	argi_Vbci=1.0/(p[13]*Vtv);
	expi=exp(argi);
	expi_argi=expi;
	expi_Vbci=expi_argi*argi_Vbci;
	Iri=p[11]*p[94]*(expi-1.0);
	Iri_expi=p[11]*p[94];
	Iri_Vbci=Iri_expi*expi_Vbci;
	q1z=1.0+qdbe*IVER+qdbc*IVEF;
	q1z_qdbe=IVER;
	q1z_qdbc=IVEF;
	q1z_Vbei=q1z_qdbe*qdbe_Vbei;
	q1z_Vbci=q1z_qdbc*qdbc_Vbci;
	q1=0.5*(sqrt((q1z-1.0e-4)*(q1z-1.0e-4)+1.0e-8)+q1z-1.0e-4)+1.0e-4;
	q1_q1z=0.5*((q1z-1.0e-4)/sqrt(((q1z-1.0e-4)*(q1z-1.0e-4))+1.0e-8)+1.0);
	q1_Vbei=q1_q1z*q1z_Vbei;
	q1_Vbci=q1_q1z*q1z_Vbci;
	q2=Ifi*IIKF+Iri*IIKR;
	q2_Ifi=IIKF;
	q2_Iri=IIKR;
	q2_Vbei=q2_Ifi*Ifi_Vbei;
	q2_Vbci=q2_Iri*Iri_Vbci;
	if(p[88]<0.5){
		xvar2=1.0/p[89];
		xvar3=pow(q1,xvar2);
		xvar3_q1=xvar3*xvar2/q1;
		xvar3_Vbei=xvar3_q1*q1_Vbei;
		xvar3_Vbci=xvar3_q1*q1_Vbci;
		xvar1=(xvar3+4.0*q2);
		xvar1_xvar3=1.0;
		xvar1_q2=4.0;
		xvar1_Vbei=xvar1_xvar3*xvar3_Vbei;
		xvar1_Vbci=xvar1_xvar3*xvar3_Vbci;
		xvar1_Vbei=xvar1_Vbei+xvar1_q2*q2_Vbei;
		xvar1_Vbci=xvar1_Vbci+xvar1_q2*q2_Vbci;
		xvar4=pow(xvar1,p[89]);
		xvar4_xvar1=xvar4*p[89]/xvar1;
		xvar4_Vbei=xvar4_xvar1*xvar1_Vbei;
		xvar4_Vbci=xvar4_xvar1*xvar1_Vbci;
		qb=0.5*(q1+xvar4);
		qb_q1=0.5;
		qb_xvar4=0.5;
		qb_Vbei=qb_q1*q1_Vbei;
		qb_Vbci=qb_q1*q1_Vbci;
		qb_Vbei=qb_Vbei+qb_xvar4*xvar4_Vbei;
		qb_Vbci=qb_Vbci+qb_xvar4*xvar4_Vbci;
	}else{
		xvar1=(1.0+4.0*q2);
		xvar1_q2=4.0;
		xvar1_Vbei=xvar1_q2*q2_Vbei;
		xvar1_Vbci=xvar1_q2*q2_Vbci;
		xvar2=pow(xvar1,p[89]);
		xvar2_xvar1=xvar2*p[89]/xvar1;
		xvar2_Vbei=xvar2_xvar1*xvar1_Vbei;
		xvar2_Vbci=xvar2_xvar1*xvar1_Vbci;
		qb=0.5*q1*(1.0+xvar2);
		qb_q1=0.5*(xvar2+1.0);
		qb_xvar2=0.5*q1;
		qb_Vbei=qb_q1*q1_Vbei;
		qb_Vbci=qb_q1*q1_Vbci;
		qb_Vbei=qb_Vbei+qb_xvar2*xvar2_Vbei;
		qb_Vbci=qb_Vbci+qb_xvar2*xvar2_Vbci;
	}
	(*Itzr)=Iri/qb;
	Itzr_Iri=1.0/qb;
	Itzr_qb=-Iri/(qb*qb);
	*Itzr_Vbci=Itzr_Iri*Iri_Vbci;
	*Itzr_Vbei=Itzr_qb*qb_Vbei;
	*Itzr_Vbci=(*Itzr_Vbci)+Itzr_qb*qb_Vbci;
	Itzf=Ifi/qb;
	Itzf_Ifi=1.0/qb;
	Itzf_qb=-Ifi/(qb*qb);
	Itzf_Vbei=Itzf_Ifi*Ifi_Vbei;
	Itzf_Vbei=Itzf_Vbei+Itzf_qb*qb_Vbei;
	Itzf_Vbci=Itzf_qb*qb_Vbci;
	(*Ixzf)=-Itzf;
	Ixzf_Itzf=-1.0;
	*Ixzf_Vbei=Ixzf_Itzf*Itzf_Vbei;
	*Ixzf_Vbci=Ixzf_Itzf*Itzf_Vbci;
	(*Itxf)=(*Vrxf);
	*Itxf_Vrxf=1.0;
	(*Ixxf)=(*Vrxf);
	*Ixxf_Vrxf=1.0;
	if(p[42]>0.0){
		argi=(*Vbep)/(p[44]*Vtv);
		argi_Vbep=1.0/(p[44]*Vtv);
		expi=exp(argi);
		expi_argi=expi;
		expi_Vbep=expi_argi*argi_Vbep;
		argx=(*Vbci)/(p[44]*Vtv);
		argx_Vbci=1.0/(p[44]*Vtv);
		expx=exp(argx);
		expx_argx=expx;
		expx_Vbci=expx_argx*argx_Vbci;
		Ifp=p[42]*(p[43]*expi+(1.0-p[43])*expx-1.0);
		Ifp_expi=p[42]*p[43];
		Ifp_expx=p[42]*(1.0-p[43]);
		Ifp_Vbep=Ifp_expi*expi_Vbep;
		Ifp_Vbci=Ifp_expx*expx_Vbci;
		q2p=Ifp*IIKP;
		q2p_Ifp=IIKP;
		q2p_Vbep=q2p_Ifp*Ifp_Vbep;
		q2p_Vbci=q2p_Ifp*Ifp_Vbci;
		qbp=0.5*(1.0+sqrt(1.0+4.0*q2p));
		qbp_q2p=1.0/sqrt(4.0*q2p+1.0);
		qbp_Vbep=qbp_q2p*q2p_Vbep;
		qbp_Vbci=qbp_q2p*q2p_Vbci;
	}else{
		Ifp=0.0;
		Ifp_Vbep=0.0;
		Ifp_Vbci=0.0;
		qbp=1.0;
		qbp_Vbep=0.0;
		qbp_Vbci=0.0;
	}
	if(p[32]==1.0){
		argi=(*Vbei)/(p[33]*Vtv);
		argi_Vbei=1.0/(p[33]*Vtv);
		expi=exp(argi);
		expi_argi=expi;
		expi_Vbei=expi_argi*argi_Vbei;
		argn=(*Vbei)/(p[35]*Vtv);
		argn_Vbei=1.0/(p[35]*Vtv);
		expn=exp(argn);
		expn_argn=expn;
		expn_Vbei=expn_argn*argn_Vbei;
		if(p[98]>0.0){
			argx=(-p[98]-(*Vbei))/(p[99]*Vtv);
			argx_Vbei=-1.0/(p[99]*Vtv);
			expx=exp(argx);
			expx_argx=expx;
			expx_Vbei=expx_argx*argx_Vbei;
			(*Ibe)=p[31]*(expi-1.0)+p[34]*(expn-1.0)-p[100]*(expx-p[104]);
			Ibe_expi=p[31];
			Ibe_expn=p[34];
			Ibe_expx=-p[100];
			*Ibe_Vbei=Ibe_expi*expi_Vbei;
			*Ibe_Vbei=(*Ibe_Vbei)+Ibe_expn*expn_Vbei;
			*Ibe_Vbei=(*Ibe_Vbei)+Ibe_expx*expx_Vbei;
		}else{
			(*Ibe)=p[31]*(expi-1.0)+p[34]*(expn-1.0);
			Ibe_expi=p[31];
			Ibe_expn=p[34];
			*Ibe_Vbei=Ibe_expi*expi_Vbei;
			*Ibe_Vbei=(*Ibe_Vbei)+Ibe_expn*expn_Vbei;
		}
		(*Ibex)=0.0;
		*Ibex_Vbex=0.0;
	}else if(p[32]==0.0){
		(*Ibe)=0.0;
		*Ibe_Vbei=0.0;
		argi=(*Vbex)/(p[33]*Vtv);
		argi_Vbex=1.0/(p[33]*Vtv);
		expi=exp(argi);
		expi_argi=expi;
		expi_Vbex=expi_argi*argi_Vbex;
		argn=(*Vbex)/(p[35]*Vtv);
		argn_Vbex=1.0/(p[35]*Vtv);
		expn=exp(argn);
		expn_argn=expn;
		expn_Vbex=expn_argn*argn_Vbex;
		if(p[98]>0.0){
			argx=(-p[98]-(*Vbex))/(p[99]*Vtv);
			argx_Vbex=-1.0/(p[99]*Vtv);
			expx=exp(argx);
			expx_argx=expx;
			expx_Vbex=expx_argx*argx_Vbex;
			(*Ibex)=p[31]*(expi-1.0)+p[34]*(expn-1.0)-p[100]*(expx-p[104]);
			Ibex_expi=p[31];
			Ibex_expn=p[34];
			Ibex_expx=-p[100];
			*Ibex_Vbex=Ibex_expi*expi_Vbex;
			*Ibex_Vbex=(*Ibex_Vbex)+Ibex_expn*expn_Vbex;
			*Ibex_Vbex=(*Ibex_Vbex)+Ibex_expx*expx_Vbex;
		}else{
			(*Ibex)=p[31]*(expi-1.0)+p[34]*(expn-1.0);
			Ibex_expi=p[31];
			Ibex_expn=p[34];
			*Ibex_Vbex=Ibex_expi*expi_Vbex;
			*Ibex_Vbex=(*Ibex_Vbex)+Ibex_expn*expn_Vbex;
		}
	}else{
		argi=(*Vbei)/(p[33]*Vtv);
		argi_Vbei=1.0/(p[33]*Vtv);
		expi=exp(argi);
		expi_argi=expi;
		expi_Vbei=expi_argi*argi_Vbei;
		argn=(*Vbei)/(p[35]*Vtv);
		argn_Vbei=1.0/(p[35]*Vtv);
		expn=exp(argn);
		expn_argn=expn;
		expn_Vbei=expn_argn*argn_Vbei;
		if(p[98]>0.0){
			argx=(-p[98]-(*Vbei))/(p[99]*Vtv);
			argx_Vbei=-1.0/(p[99]*Vtv);
			expx=exp(argx);
			expx_argx=expx;
			expx_Vbei=expx_argx*argx_Vbei;
			(*Ibe)=p[32]*(p[31]*(expi-1.0)+p[34]*(expn-1.0)-p[100]*(expx-p[104]));
			Ibe_expi=p[31]*p[32];
			Ibe_expn=p[34]*p[32];
			Ibe_expx=-p[100]*p[32];
			*Ibe_Vbei=Ibe_expi*expi_Vbei;
			*Ibe_Vbei=(*Ibe_Vbei)+Ibe_expn*expn_Vbei;
			*Ibe_Vbei=(*Ibe_Vbei)+Ibe_expx*expx_Vbei;
		}else{
			(*Ibe)=p[32]*(p[31]*(expi-1.0)+p[34]*(expn-1.0));
			Ibe_expi=p[31]*p[32];
			Ibe_expn=p[34]*p[32];
			*Ibe_Vbei=Ibe_expi*expi_Vbei;
			*Ibe_Vbei=(*Ibe_Vbei)+Ibe_expn*expn_Vbei;
		}
		argi=(*Vbex)/(p[33]*Vtv);
		argi_Vbex=1.0/(p[33]*Vtv);
		expi=exp(argi);
		expi_argi=expi;
		expi_Vbex=expi_argi*argi_Vbex;
		argn=(*Vbex)/(p[35]*Vtv);
		argn_Vbex=1.0/(p[35]*Vtv);
		expn=exp(argn);
		expn_argn=expn;
		expn_Vbex=expn_argn*argn_Vbex;
		if(p[98]>0.0){
			argx=(-p[98]-(*Vbex))/(p[99]*Vtv);
			argx_Vbex=-1.0/(p[99]*Vtv);
			expx=exp(argx);
			expx_argx=expx;
			expx_Vbex=expx_argx*argx_Vbex;
			(*Ibex)=(1.0-p[32])*(p[31]*(expi-1.0)+p[34]*(expn-1.0)-p[100]*(expx-p[104]));
			Ibex_expi=p[31]*(1.0-p[32]);
			Ibex_expn=p[34]*(1.0-p[32]);
			Ibex_expx=-p[100]*(1.0-p[32]);
			*Ibex_Vbex=Ibex_expi*expi_Vbex;
			*Ibex_Vbex=(*Ibex_Vbex)+Ibex_expn*expn_Vbex;
			*Ibex_Vbex=(*Ibex_Vbex)+Ibex_expx*expx_Vbex;
		}else{
			(*Ibex)=(1.0-p[32])*(p[31]*(expi-1.0)+p[34]*(expn-1.0));
			Ibex_expi=p[31]*(1.0-p[32]);
			Ibex_expn=p[34]*(1.0-p[32]);
			*Ibex_Vbex=Ibex_expi*expi_Vbex;
			*Ibex_Vbex=(*Ibex_Vbex)+Ibex_expn*expn_Vbex;
		}
	}
	argi=(*Vbci)/(p[37]*Vtv);
	argi_Vbci=1.0/(p[37]*Vtv);
	expi=exp(argi);
	expi_argi=expi;
	expi_Vbci=expi_argi*argi_Vbci;
	argn=(*Vbci)/(p[39]*Vtv);
	argn_Vbci=1.0/(p[39]*Vtv);
	expn=exp(argn);
	expn_argn=expn;
	expn_Vbci=expn_argn*argn_Vbci;
	Ibcj=p[36]*(expi-1.0)+p[38]*(expn-1.0);
	Ibcj_expi=p[36];
	Ibcj_expn=p[38];
	Ibcj_Vbci=Ibcj_expi*expi_Vbci;
	Ibcj_Vbci=Ibcj_Vbci+Ibcj_expn*expn_Vbci;
	if((p[45]>0.0)||(p[46]>0.0)){
		argi=(*Vbep)/(p[37]*Vtv);
		argi_Vbep=1.0/(p[37]*Vtv);
		expi=exp(argi);
		expi_argi=expi;
		expi_Vbep=expi_argi*argi_Vbep;
		argn=(*Vbep)/(p[39]*Vtv);
		argn_Vbep=1.0/(p[39]*Vtv);
		expn=exp(argn);
		expn_argn=expn;
		expn_Vbep=expn_argn*argn_Vbep;
		(*Ibep)=p[45]*(expi-1.0)+p[46]*(expn-1.0);
		Ibep_expi=p[45];
		Ibep_expn=p[46];
		*Ibep_Vbep=Ibep_expi*expi_Vbep;
		*Ibep_Vbep=(*Ibep_Vbep)+Ibep_expn*expn_Vbep;
	}else{
		(*Ibep)=0.0;
		*Ibep_Vbep=0.0;
	}
	if(p[40]>0.0){
		vl=0.5*(sqrt((p[24]-(*Vbci))*(p[24]-(*Vbci))+0.01)+(p[24]-(*Vbci)));
		vl_Vbci=0.5*(-(p[24]-(*Vbci))/sqrt(((p[24]-(*Vbci))*(p[24]-(*Vbci)))+0.01)-1.0);
		xvar2=(p[25]-1.0);
		xvar3=pow(vl,xvar2);
		xvar3_vl=xvar3*xvar2/vl;
		xvar3_Vbci=xvar3_vl*vl_Vbci;
		xvar1=-p[41]*xvar3;
		xvar1_xvar3=-p[41];
		xvar1_Vbci=xvar1_xvar3*xvar3_Vbci;
		xvar4=exp(xvar1);
		xvar4_xvar1=xvar4;
		xvar4_Vbci=xvar4_xvar1*xvar1_Vbci;
		avalf=p[40]*vl*xvar4;
		avalf_vl=p[40]*xvar4;
		avalf_xvar4=p[40]*vl;
		avalf_Vbci=avalf_vl*vl_Vbci;
		avalf_Vbci=avalf_Vbci+avalf_xvar4*xvar4_Vbci;
		Igc=((*Itxf)-(*Itzr)-Ibcj)*avalf;
		Igc_Itxf=avalf;
		Igc_Itzr=-avalf;
		Igc_Ibcj=-avalf;
		Igc_avalf=-(*Itzr)+(*Itxf)-Ibcj;
		Igc_Vrxf=Igc_Itxf*(*Itxf_Vrxf);
		Igc_Vbci=Igc_Itzr*(*Itzr_Vbci);
		Igc_Vbei=Igc_Itzr*(*Itzr_Vbei);
		Igc_Vbci=Igc_Vbci+Igc_Ibcj*Ibcj_Vbci;
		Igc_Vbci=Igc_Vbci+Igc_avalf*avalf_Vbci;
	}else{
		Igc=0.0;
		Igc_Vrxf=0.0;
		Igc_Vbci=0.0;
		Igc_Vbei=0.0;
	}
	(*Ibc)=Ibcj-Igc;
	Ibc_Ibcj=1.0;
	Ibc_Igc=-1.0;
	*Ibc_Vbci=Ibc_Ibcj*Ibcj_Vbci;
	*Ibc_Vrxf=Ibc_Igc*Igc_Vrxf;
	*Ibc_Vbci=(*Ibc_Vbci)+Ibc_Igc*Igc_Vbci;
	*Ibc_Vbei=Ibc_Igc*Igc_Vbei;
	if(p[1]>0.0){
		(*Ircx)=(*Vrcx)/p[1];
		*Ircx_Vrcx=1.0/p[1];
	}else{
		(*Ircx)=0.0;
		*Ircx_Vrcx=0.0;
	}
	argi=(*Vbci)/Vtv;
	argi_Vbci=1.0/Vtv;
	expi=exp(argi);
	expi_argi=expi;
	expi_Vbci=expi_argi*argi_Vbci;
	argx=(*Vbcx)/Vtv;
	argx_Vbcx=1.0/Vtv;
	expx=exp(argx);
	expx_argx=expx;
	expx_Vbcx=expx_argx*argx_Vbcx;
	Kbci=sqrt(1.0+p[4]*expi);
	Kbci_expi=p[4]/(2.0*sqrt(expi*p[4]+1.0));
	Kbci_Vbci=Kbci_expi*expi_Vbci;
	Kbcx=sqrt(1.0+p[4]*expx);
	Kbcx_expx=p[4]/(2.0*sqrt(expx*p[4]+1.0));
	Kbcx_Vbcx=Kbcx_expx*expx_Vbcx;
	if(p[2]>0.0){
		rKp1=(Kbci+1.0)/(Kbcx+1.0);
		rKp1_Kbci=1.0/(Kbcx+1.0);
		rKp1_Kbcx=-(Kbci+1.0)/((Kbcx+1.0)*(Kbcx+1.0));
		rKp1_Vbci=rKp1_Kbci*Kbci_Vbci;
		rKp1_Vbcx=rKp1_Kbcx*Kbcx_Vbcx;
		xvar1=log(rKp1);
		xvar1_rKp1=1.0/rKp1;
		xvar1_Vbci=xvar1_rKp1*rKp1_Vbci;
		xvar1_Vbcx=xvar1_rKp1*rKp1_Vbcx;
		Iohm=((*Vrci)+Vtv*(Kbci-Kbcx-xvar1))/p[2];
		Iohm_Vrci=1.0/p[2];
		Iohm_Kbci=Vtv/p[2];
		Iohm_Kbcx=-Vtv/p[2];
		Iohm_xvar1=-Vtv/p[2];
		Iohm_Vbci=Iohm_Kbci*Kbci_Vbci;
		Iohm_Vbcx=Iohm_Kbcx*Kbcx_Vbcx;
		Iohm_Vbci=Iohm_Vbci+Iohm_xvar1*xvar1_Vbci;
		Iohm_Vbcx=Iohm_Vbcx+Iohm_xvar1*xvar1_Vbcx;
		derf=IVO*p[2]*Iohm/(1.0+0.5*IVO*IHRCF*sqrt((*Vrci)*(*Vrci)+0.01));
		derf_Iohm=IVO*p[2]/(0.5*IHRCF*IVO*sqrt(((*Vrci)*(*Vrci))+0.01)+1.0);
		derf_Vrci=-0.5*IHRCF*Iohm*(IVO*IVO)*p[2]*(*Vrci)/(sqrt(((*Vrci)*(*Vrci))+0.01)*((0.5*IHRCF*IVO*sqrt(((*Vrci)*(*Vrci))+0.01)+1.0)*(0.5*IHRCF*IVO*sqrt(((*Vrci)*(*Vrci))+0.01)+1.0)));
		derf_Vrci=derf_Vrci+derf_Iohm*Iohm_Vrci;
		derf_Vbci=derf_Iohm*Iohm_Vbci;
		derf_Vbcx=derf_Iohm*Iohm_Vbcx;
		(*Irci)=Iohm/sqrt(1.0+derf*derf);
		Irci_Iohm=1.0/sqrt((derf*derf)+1.0);
		Irci_derf=-derf*Iohm/pow(((derf*derf)+1.0),(3.0/2.0));
		*Irci_Vrci=Irci_Iohm*Iohm_Vrci;
		*Irci_Vbci=Irci_Iohm*Iohm_Vbci;
		*Irci_Vbcx=Irci_Iohm*Iohm_Vbcx;
		*Irci_Vrci=(*Irci_Vrci)+Irci_derf*derf_Vrci;
		*Irci_Vbci=(*Irci_Vbci)+Irci_derf*derf_Vbci;
		*Irci_Vbcx=(*Irci_Vbcx)+Irci_derf*derf_Vbcx;
	}else{
		(*Irci)=0.0;
		*Irci_Vrci=0.0;
		*Irci_Vbci=0.0;
		*Irci_Vbcx=0.0;
	}
	if(p[6]>0.0){
		(*Irbx)=(*Vrbx)/p[6];
		*Irbx_Vrbx=1.0/p[6];
	}else{
		(*Irbx)=0.0;
		*Irbx_Vrbx=0.0;
	}
	if(p[7]>0.0){
		(*Irbi)=(*Vrbi)*qb/p[7];
		*Irbi_Vrbi=qb/p[7];
		Irbi_qb=(*Vrbi)/p[7];
		*Irbi_Vbei=Irbi_qb*qb_Vbei;
		*Irbi_Vbci=Irbi_qb*qb_Vbci;
	}else{
		(*Irbi)=0.0;
		*Irbi_Vrbi=0.0;
		*Irbi_Vbei=0.0;
		*Irbi_Vbci=0.0;
	}
	if(p[8]>0.0){
		(*Ire)=(*Vre)/p[8];
		*Ire_Vre=1.0/p[8];
	}else{
		(*Ire)=0.0;
		*Ire_Vre=0.0;
	}
	if(p[10]>0.0){
		(*Irbp)=(*Vrbp)*qbp/p[10];
		*Irbp_Vrbp=qbp/p[10];
		Irbp_qbp=(*Vrbp)/p[10];
		*Irbp_Vbep=Irbp_qbp*qbp_Vbep;
		*Irbp_Vbci=Irbp_qbp*qbp_Vbci;
	}else{
		(*Irbp)=0.0;
		*Irbp_Vrbp=0.0;
		*Irbp_Vbep=0.0;
		*Irbp_Vbci=0.0;
	}
	if(Ifi>0.0){
		sgIf=1.0;
	}else{
		sgIf=0.0;
	}
	rIf=Ifi*sgIf*IITF;
	rIf_Ifi=IITF*sgIf;
	rIf_Vbei=rIf_Ifi*Ifi_Vbei;
	mIf=rIf/(rIf+1.0);
	mIf_rIf=1.0/(rIf+1.0)-rIf/((rIf+1.0)*(rIf+1.0));
	mIf_Vbei=mIf_rIf*rIf_Vbei;
	xvar1=(*Vbci)*IVTF/1.44;
	xvar1_Vbci=0.6944444*IVTF;
	xvar2=exp(xvar1);
	xvar2_xvar1=xvar2;
	xvar2_Vbci=xvar2_xvar1*xvar1_Vbci;
	tff=p[56]*(1.0+p[57]*q1)*(1.0+p[58]*xvar2*(slTF+mIf*mIf)*sgIf);
	tff_q1=p[57]*p[56]*(sgIf*(slTF+(mIf*mIf))*p[58]*xvar2+1.0);
	tff_xvar2=(q1*p[57]+1.0)*sgIf*(slTF+(mIf*mIf))*p[56]*p[58];
	tff_mIf=2.0*mIf*(q1*p[57]+1.0)*sgIf*p[56]*p[58]*xvar2;
	tff_Vbei=tff_q1*q1_Vbei;
	tff_Vbci=tff_q1*q1_Vbci;
	tff_Vbci=tff_Vbci+tff_xvar2*xvar2_Vbci;
	tff_Vbei=tff_Vbei+tff_mIf*mIf_Vbei;
	(*Qbe)=p[16]*qdbe*p[32]+tff*Ifi/qb;
	Qbe_qdbe=p[16]*p[32];
	Qbe_tff=Ifi/qb;
	Qbe_Ifi=tff/qb;
	Qbe_qb=-Ifi*tff/(qb*qb);
	*Qbe_Vbei=Qbe_qdbe*qdbe_Vbei;
	*Qbe_Vbei=(*Qbe_Vbei)+Qbe_tff*tff_Vbei;
	*Qbe_Vbci=Qbe_tff*tff_Vbci;
	*Qbe_Vbei=(*Qbe_Vbei)+Qbe_Ifi*Ifi_Vbei;
	*Qbe_Vbei=(*Qbe_Vbei)+Qbe_qb*qb_Vbei;
	*Qbe_Vbci=(*Qbe_Vbci)+Qbe_qb*qb_Vbci;
	(*Qbex)=p[16]*qdbex*(1.0-p[32]);
	Qbex_qdbex=p[16]*(1.0-p[32]);
	*Qbex_Vbex=Qbex_qdbex*qdbex_Vbex;
	(*Qbc)=p[21]*qdbc+p[61]*Iri+p[22]*Kbci;
	Qbc_qdbc=p[21];
	Qbc_Iri=p[61];
	Qbc_Kbci=p[22];
	*Qbc_Vbci=Qbc_qdbc*qdbc_Vbci;
	*Qbc_Vbci=(*Qbc_Vbci)+Qbc_Iri*Iri_Vbci;
	*Qbc_Vbci=(*Qbc_Vbci)+Qbc_Kbci*Kbci_Vbci;
	(*Qbcx)=p[22]*Kbcx;
	Qbcx_Kbcx=p[22];
	*Qbcx_Vbcx=Qbcx_Kbcx*Kbcx_Vbcx;
	(*Qbep)=p[23]*qdbep+p[61]*Ifp;
	Qbep_qdbep=p[23];
	Qbep_Ifp=p[61];
	*Qbep_Vbep=Qbep_qdbep*qdbep_Vbep;
	*Qbep_Vbep=(*Qbep_Vbep)+Qbep_Ifp*Ifp_Vbep;
	*Qbep_Vbci=Qbep_Ifp*Ifp_Vbci;
	(*Qbeo)=(*Vbe)*p[15];
	*Qbeo_Vbe=p[15];
	(*Qbco)=(*Vbc)*p[20];
	*Qbco_Vbc=p[20];
	(*Flxf)=LEP*(*Ixxf);
	Flxf_Ixxf=LEP;
	*Flxf_Vrxf=Flxf_Ixxf*(*Ixxf_Vrxf);
	(*Qcxf)=CEP*(*Vcxf);
	*Qcxf_Vcxf=CEP;

/*	Scale outputs */

	if((*SCALE)!=1.0){
		*Ibe=(*SCALE)*(*Ibe);
		*Ibe_Vbei=(*SCALE)*(*Ibe_Vbei);
		*Ibex=(*SCALE)*(*Ibex);
		*Ibex_Vbex=(*SCALE)*(*Ibex_Vbex);
		*Itxf=(*SCALE)*(*Itxf);
		*Itxf_Vrxf=(*SCALE)*(*Itxf_Vrxf);
		*Itzr=(*SCALE)*(*Itzr);
		*Itzr_Vbci=(*SCALE)*(*Itzr_Vbci);
		*Itzr_Vbei=(*SCALE)*(*Itzr_Vbei);
		*Ibc=(*SCALE)*(*Ibc);
		*Ibc_Vbci=(*SCALE)*(*Ibc_Vbci);
		*Ibc_Vrxf=(*SCALE)*(*Ibc_Vrxf);
		*Ibc_Vbei=(*SCALE)*(*Ibc_Vbei);
		*Ibep=(*SCALE)*(*Ibep);
		*Ibep_Vbep=(*SCALE)*(*Ibep_Vbep);
		*Ircx=(*SCALE)*(*Ircx);
		*Ircx_Vrcx=(*SCALE)*(*Ircx_Vrcx);
		*Irci=(*SCALE)*(*Irci);
		*Irci_Vrci=(*SCALE)*(*Irci_Vrci);
		*Irci_Vbci=(*SCALE)*(*Irci_Vbci);
		*Irci_Vbcx=(*SCALE)*(*Irci_Vbcx);
		*Irbx=(*SCALE)*(*Irbx);
		*Irbx_Vrbx=(*SCALE)*(*Irbx_Vrbx);
		*Irbi=(*SCALE)*(*Irbi);
		*Irbi_Vrbi=(*SCALE)*(*Irbi_Vrbi);
		*Irbi_Vbei=(*SCALE)*(*Irbi_Vbei);
		*Irbi_Vbci=(*SCALE)*(*Irbi_Vbci);
		*Ire=(*SCALE)*(*Ire);
		*Ire_Vre=(*SCALE)*(*Ire_Vre);
		*Irbp=(*SCALE)*(*Irbp);
		*Irbp_Vrbp=(*SCALE)*(*Irbp_Vrbp);
		*Irbp_Vbep=(*SCALE)*(*Irbp_Vbep);
		*Irbp_Vbci=(*SCALE)*(*Irbp_Vbci);
		*Qbe=(*SCALE)*(*Qbe);
		*Qbe_Vbei=(*SCALE)*(*Qbe_Vbei);
		*Qbe_Vbci=(*SCALE)*(*Qbe_Vbci);
		*Qbex=(*SCALE)*(*Qbex);
		*Qbex_Vbex=(*SCALE)*(*Qbex_Vbex);
		*Qbc=(*SCALE)*(*Qbc);
		*Qbc_Vbci=(*SCALE)*(*Qbc_Vbci);
		*Qbcx=(*SCALE)*(*Qbcx);
		*Qbcx_Vbcx=(*SCALE)*(*Qbcx_Vbcx);
		*Qbep=(*SCALE)*(*Qbep);
		*Qbep_Vbep=(*SCALE)*(*Qbep_Vbep);
		*Qbep_Vbci=(*SCALE)*(*Qbep_Vbci);
		*Qbeo=(*SCALE)*(*Qbeo);
		*Qbeo_Vbe=(*SCALE)*(*Qbeo_Vbe);
		*Qbco=(*SCALE)*(*Qbco);
		*Qbco_Vbc=(*SCALE)*(*Qbco_Vbc);
		*Ixzf=(*SCALE)*(*Ixzf);
		*Ixzf_Vbei=(*SCALE)*(*Ixzf_Vbei);
		*Ixzf_Vbci=(*SCALE)*(*Ixzf_Vbci);
		*Ixxf=(*SCALE)*(*Ixxf);
		*Ixxf_Vrxf=(*SCALE)*(*Ixxf_Vrxf);
		*Qcxf=(*SCALE)*(*Qcxf);
		*Qcxf_Vcxf=(*SCALE)*(*Qcxf_Vcxf);
		*Flxf=(*SCALE)*(*Flxf);
		*Flxf_Vrxf=(*SCALE)*(*Flxf_Vrxf);
	}
	return(0);
}
