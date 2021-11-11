#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353,inv2=499122177;
ll a[1<<17],b[1<<17],tmp[1<<17],c[1<<17];
int n;
void FWT_OR(ll *a,int rev){
	if (rev==1){
		for (int l=2;l<=n;l<<=1)
			for (int st=0;st<n;st+=l)
				for (int i=0;i<(l>>1);++i)
					(a[st+(l>>1)+i]+=a[st+i])%=mod;
	}
	else{
		for (int l=n;l>=2;l>>=1)
			for (int st=0;st<n;st+=l)
				for (int i=0;i<(l>>1);++i)
					(a[st+(l>>1)+i]+=mod-a[st+i])%=mod;
	}
}
void FWT_AND(ll *a,int rev){
	if (rev==1){
		for (int l=2;l<=n;l<<=1)
			for (int st=0;st<n;st+=l)
				for (int i=0;i<(l>>1);++i)
					(a[st+i]+=a[st+(l>>1)+i])%=mod;
	}
	else{
		for (int l=n;l>=2;l>>=1)
			for (int st=0;st<n;st+=l)
				for (int i=0;i<(l>>1);++i)
					(a[st+i]+=mod-a[st+(l>>1)+i])%=mod;
	}
}
void FWT_XOR(ll *a,int rev){
	if (rev==1){
		for (int l=2;l<=n;l<<=1)
			for (int st=0;st<n;st+=l)
				for (int i=0;i<(l>>1);++i){
					ll L=(a[st+i]+a[st+(l>>1)+i])%mod;
					ll R=(a[st+i]-a[st+(l>>1)+i]+mod)%mod;
					a[st+i]=L;
					a[st+(l>>1)+i]=R;
				}
	}
	else{
		for (int l=n;l>=2;l>>=1)
			for (int st=0;st<n;st+=l)
				for (int i=0;i<(l>>1);++i){
					ll L=(a[st+i]+a[st+(l>>1)+i])%mod*inv2%mod;
					ll R=(a[st+i]-a[st+(l>>1)+i]+mod)%mod*inv2%mod;
					a[st+i]=L;
					a[st+(l>>1)+i]=R;
				}
	}
}
int main(){
	scanf("%d",&n);n=(1<<n);
	for (int i=0;i<n;++i) scanf("%lld",&a[i]);
	for (int i=0;i<n;++i) scanf("%lld",&b[i]);
	
	FWT_OR(a,1);
	FWT_OR(b,1);
	for (int i=0;i<n;++i) c[i]=a[i]*b[i]%mod;
	FWT_OR(a,-1);
	FWT_OR(b,-1);
	FWT_OR(c,-1);
	for (int i=0;i<n;++i) printf("%lld ",c[i]);puts("");
	
	FWT_AND(a,1);
	FWT_AND(b,1);
	for (int i=0;i<n;++i) c[i]=a[i]*b[i]%mod;
	FWT_AND(a,-1);
	FWT_AND(b,-1);
	FWT_AND(c,-1);
	for (int i=0;i<n;++i) printf("%lld ",c[i]);puts("");
	
	FWT_XOR(a,1);
	FWT_XOR(b,1);
	for (int i=0;i<n;++i) c[i]=a[i]*b[i]%mod;
	FWT_XOR(a,-1);
	FWT_XOR(b,-1);
	FWT_XOR(c,-1);
	for (int i=0;i<n;++i) printf("%lld ",c[i]);puts("");
}
