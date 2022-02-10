#include <fstream>
#include <math.h>

using namespace std;

const int ROW = 600;
const int COL = 600;
int rays = 10000000;
int R = 100;

int imageBuff[ROW][COL];

ofstream outFile;

using namespace std;


// Determines if a ray will hit the sphere
bool isInSphere(int x,int y){
    int h = COL/2;
    int k = ROW/2;
    return ( sqrt(pow(x-h,2) + pow(y-k,2)) <= R);
}

//returns a depth value of the sphere
float depth(int x, int y){
    int h = COL/2;
    int k = ROW/2;
    float Z = sqrt(pow(x-h,2) + pow(y-k,2) + pow(R,2));
    return Z;
}

//fire rays at the sphere and return a normalized depth value
void rayTrace(){
    int x = rand() % COL;
    int y = rand()% ROW;
    if(isInSphere(x,y)){
        float Z = depth(x,y);
        if(Z > 0)imageBuff[x][y] = 255*(Z-142)/-40; // used in place of surface reflection calculation
    }else imageBuff[x][y] = 0;
}

//save the output as a *.ppm file
void write_image(){
    outFile.open("output.ppm");
    outFile << "P2\n";
    outFile << ROW << " " << COL << " 256\n";
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            outFile << imageBuff[i][j] << " ";
        }
        outFile << "\n";
    } 
    outFile.close();
}

//Main function
int main(){
    srand(time(NULL));

    for(int i=0;i<rays;i++){
        rayTrace();
    }
    write_image();
    return 0;
}

