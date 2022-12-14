#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;


#define NUM 10000000

typedef struct {
    float x;
    float y;
} Point;

float fRand(float fMin, float fMax) {
    float f = (float) rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

Point pRand() {
    float x, y;
    Point p;
    do {
        x = fRand(-1, 1);
        y = fRand(-1, 1);
    } while (x * x + y * y < 1);
    p.x = x;
    p.y = y;
    return p;
}

float cross_3(Point a, Point b) {
    return a.x * b.y - b.x * a.y;
}

bool isSameSign(float *n_array, int len) {
    for (int k = 0; k < len; k++) {
        for (int j = k; j < len; j++) {
            if (n_array[k] * n_array[j] < 0) {
                return false;
            }
        }
    }
    return true;
}



bool isInSemiCircle(Point *p_array, int len) {
    float *c3 = static_cast<float *>(malloc((len - 1) * sizeof(float)));

    for(int j=0;j<len;j++){
        int index=0;
        for (int k = 0; k < len; k++) {
            if(k!=j){
                c3[index] = cross_3(p_array[j], p_array[k]);
                index++;
            }
        }
        bool result = isSameSign(c3, len - 1);
        if(result){
            free(c3);
            return true;
        }
    }

    free(c3);
    return false;
}



int main() {
    auto start = high_resolution_clock::now();

    int s = 0;
    int p_num = 4;

    srand(time(NULL));

    Point *p_array = static_cast<Point *>(malloc(p_num * sizeof(Point)));
    for (int k = 0; k < NUM; k++) {
        for (int j = 0; j < p_num; j++) {
            p_array[j] = pRand();
        }
        if (isInSemiCircle(p_array, p_num)) {
            s++;
        }
    }
    float p = (float) s / NUM;
    std::cout << "probability: " << p << std::endl;
    free(p_array);


    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
    return 0;
}
