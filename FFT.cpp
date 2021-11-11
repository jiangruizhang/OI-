#include<bits/stdc++.h>
using namespace std;
const int N=1<<22;
typedef complex<double> comp;
comp f[N],g[N],h[N];
int r[N];
int nf,ng,nh=1;
void FFT(comp *f,int rev){//rev=1->DFT  rev=-1->IDFT
	for (int i=0;i<nh;++i) if (r[i]<i) swap(f[i],f[r[i]]);
	for (int l=2;l<=nh;l<<=1){
		for (int i=0;i<nh;i+=l){
			comp step=comp(cos(2.0*M_PI/l),sin(2.0*M_PI/l)*rev),mul=comp(1,0);
			for (int j=0;j<(l>>1);++j){
				comp tmp=f[i+j+(l>>1)];
				f[i+j+(l>>1)]=f[i+j]-mul*tmp;
				f[i+j]=f[i+j]+mul*tmp;
				mul=mul*step;
			}
		}
	}
}
int main(){
	scanf("%d%d",&nf,&ng);
	while (nh-1<nf+ng)
		nh<<=1;
	for (int i=0;i<=nf;++i){double x;scanf("%lf",&x);f[i]=comp(x,0);}
	for (int i=0;i<=ng;++i){double x;scanf("%lf",&x);g[i]=comp(x,0);}
	r[0]=0; 
	for (int i=1;i<nh;++i) r[i]=(r[i>>1]>>1)|(i&1?(nh>>1):0);
	FFT(f,1);
	FFT(g,1);
	for (int i=0;i<nh;++i) h[i]=f[i]*g[i];
	FFT(h,-1);
	for (int i=0;i<=nf+ng;++i) printf("%d ",(int)round(h[i].real()/nh));
}
