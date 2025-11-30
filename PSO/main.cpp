#include <bits/stdc++.h>
using namespace std;

struct Particle {
    double x, y;          // vị trí
    double vx, vy;        // vận tốc
    double pbest_x, pbest_y; // vị trí tốt nhất cá nhân
    double pbest_value;   // giá trị tốt nhất cá nhân
};

double objective(double x, double y) {
    return x*x + y*y;
}

int main() {
    srand(time(NULL));

    int swarm_size = 30;
    int max_iter = 200;
    double w = 0.7;       // inertia weight
    double c1 = 1.5;      // cognitive component
    double c2 = 1.5;      // social component

    vector<Particle> swarm(swarm_size);

    double gbest_x = 0, gbest_y = 0;
    double gbest_value = 1e18;

    //Khởi tạo
    for (int i = 0; i < swarm_size; i++) {
        swarm[i].x = ((rand() % 2001) - 1000) / 100.0;
        swarm[i].y = ((rand() % 2001) - 1000) / 100.0;

        swarm[i].vx = ((rand() % 2001) - 1000) / 500.0;
        swarm[i].vy = ((rand() % 2001) - 1000) / 500.0;

        double val = objective(swarm[i].x, swarm[i].y);

        swarm[i].pbest_x = swarm[i].x;
        swarm[i].pbest_y = swarm[i].y;
        swarm[i].pbest_value = val;

        if (val < gbest_value) {
            gbest_value = val;
            gbest_x = swarm[i].x;
            gbest_y = swarm[i].y;
        }
    }

    for (int iter = 0; iter < max_iter; iter++) {
        for (int i = 0; i < swarm_size; i++) {
            double r1 = (double)rand() / RAND_MAX;
            double r2 = (double)rand() / RAND_MAX;

            // Cập nhật vận tốc
            swarm[i].vx = w * swarm[i].vx
                        + c1 * r1 * (swarm[i].pbest_x - swarm[i].x)
                        + c2 * r2 * (gbest_x - swarm[i].x);

            swarm[i].vy = w * swarm[i].vy
                        + c1 * r1 * (swarm[i].pbest_y - swarm[i].y)
                        + c2 * r2 * (gbest_y - swarm[i].y);

            // Cập nhật vị trí
            swarm[i].x += swarm[i].vx;
            swarm[i].y += swarm[i].vy;

            double val = objective(swarm[i].x, swarm[i].y);

            // Cập nhật pbest
            if (val < swarm[i].pbest_value) {
                swarm[i].pbest_value = val;
                swarm[i].pbest_x = swarm[i].x;
                swarm[i].pbest_y = swarm[i].y;
            }

            // Cập nhật gbest
            if (val < gbest_value) {
                gbest_value = val;
                gbest_x = swarm[i].x;
                gbest_y = swarm[i].y;
            }
        }
    }

    cout << "Ket qua PSO:" << endl;
    cout << "x = " << gbest_x << endl;
    cout << "y = " << gbest_y << endl;
    cout << "Gia tri f(x,y) = " << gbest_value << endl;

    return 0;
}
