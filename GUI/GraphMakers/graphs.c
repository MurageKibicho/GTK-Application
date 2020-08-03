#include<stdio.h>
#include <stdlib.h>
#include<math.h>


double theta30(double x){
  double out=3.0*sqrt(14.0)/4.0*(5.0/3.0*pow(cos(x),3)-cos(x));
  return out;
}
double theta31(double x){
  double out=(sqrt(42))/(8)*sin(x)*(5*pow(cos(x),2)-1);
  return out;
}
double theta32(double x){
  double out=sqrt(105)/4*pow(sin(x),2)*cos(x);
  return out;
}
double theta33(double x){
  double out=(sqrt(70))/(8)*(pow(sin(x),3));
  return out;
}


typedef struct {
	double x, y;
}point;

double shoeLace(char *inputFile) {
	int i, numPoints;
	double leftSum = 0, rightSum = 0, result = 0;
	point *pointSet;
	FILE* fp = fopen(inputFile, "r");
	fscanf(fp, "%d", &numPoints);
	printf("%d\n",numPoints);

	pointSet = (point*)malloc((numPoints + 1)*sizeof(point));
	for(i = 0; i < numPoints; i++) {
		fscanf(fp, "%lf %lf", &pointSet[i].x, &pointSet[i].y);
	}
	fclose(fp);

	pointSet[numPoints] = pointSet[0];
	for(i = 0; i < numPoints; i++) {
		leftSum  +=pointSet[i].x*pointSet[i+1].y;
		rightSum +=pointSet[i+1].x*pointSet[i].y;
	}
	free(pointSet);
	result = 0.5*fabs(leftSum - rightSum);
	printf("%f\n", result);

	return result;
}

int main(){
  double theta;
  double x1,x2,x3,x4,y1,y2,y3,y4;
  FILE *fp1=NULL;
  FILE *fp2=NULL;
  FILE *fp3=NULL;
  FILE *fp4=NULL;
  //fp1=fopen("orbital1.txt","w");
  fp2=fopen("orbital2.txt","w");
  fp3=fopen("orbital3.txt","w");
  fp4=fopen("orbital4.txt","w");
  for(theta=0;theta<=2*M_PI;theta=theta+0.01){
    x1=theta30(theta)*theta30(theta)*cos(theta);
    x2=theta31(theta)*theta31(theta)*cos(theta);
    x3=theta32(theta)*theta32(theta)*cos(theta);
    x4=theta33(theta)*theta33(theta)*cos(theta);
    y1=theta30(theta)*theta30(theta)*sin(theta);
    y2=theta31(theta)*theta31(theta)*sin(theta);
    y3=theta32(theta)*theta32(theta)*sin(theta);
    y4=theta33(theta)*theta33(theta)*sin(theta);
   // fprintf(fp1,"%lf\t%lf\n",x1,y1);
    fprintf(fp2,"%lf\t%lf\n",x2,y2);
    fprintf(fp3,"%lf\t%lf\n",x3,y3);
    fprintf(fp4,"%lf\t%lf\n",x4,y4);
  }
  shoeLace("orbital1.txt");
  system("gnuplot -p gnuscript.sh");
  return 0;
}
	
