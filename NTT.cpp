#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int N=1<<22;
int f[N],g[N],h[N];
int r[N];
int nf,ng,nh=1;
int ksm(int x,int y){
	int res=1;
	while (y){
		if (y&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return res;
}
void FFT(int *f,int rev){//rev=1->DFT  rev=-1->IDFT
	for (int i=0;i<nh;++i) if (r[i]<i) swap(f[i],f[r[i]]);
	for (int l=2;l<=nh;l<<=1){
		for (int i=0;i<nh;i+=l){
			int step=ksm(3,(mod-1)/l),mul=1;
			for (int j=0;j<(l>>1);++j){
				int tmp=f[i+j+(l>>1)];
				f[i+j+(l>>1)]=(1ll*f[i+j]-1ll*mul*tmp%mod+mod)%mod;
				f[i+j]=(1ll*f[i+j]+1ll*mul*tmp%mod)%mod;
				mul=1ll*mul*step%mod;
			}
		}
	}
	if (rev==-1){
		reverse(f+1,f+nh);
		int inv=ksm(nh,mod-2);
		for (int i=0;i<nh;++i) f[i]=1ll*f[i]*inv%mod;
	}
}
int main(){
	scanf("%d%d",&nf,&ng);
	while (nh-1<nf+ng) nh<<=1;
	for (int i=0;i<=nf;++i) scanf("%d",&f[i]);
	for (int i=0;i<=ng;++i) scanf("%d",&g[i]) ;
	r[0]=0; 
	for (int i=1;i<nh;++i) r[i]=(r[i>>1]>>1)|(i&1?(nh>>1):0);
	FFT(f,1);
	FFT(g,1);
	for (int i=0;i<nh;++i) h[i]=1ll*f[i]*g[i]%mod;
	FFT(h,-1);
	for (int i=0;i<=nf+ng;++i) printf("%lld ",h[i]);
}
