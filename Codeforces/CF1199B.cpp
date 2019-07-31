#include<cstdio>

int main(){
	double h,l;
	scanf("%lf%lf", &h, &l);
	printf("%.10lf\n", (h * h + l * l) / (2 * h) - h);
	return 0;
}
