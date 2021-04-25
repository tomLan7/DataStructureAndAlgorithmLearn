
#include <iostream>
#include<vector>
//7 0 1 1 3 3 2 6 3 4 5 2 1 3
using namespace std;
int main()
{
    int N, Q;
    cin >> N;
    vector<pair<int,int>> p;//每个节点second存储子节点个数(不包括自身)。
    p.resize(N);
    for (int i = 1; i < N;i++) {
        cin >> p[i].first;
        
        for (int j=p[i].first;;j=p[j].first) {//向上遍历让所有加1
            p[j].second += 1;
            if (j == 0) {
                break;
            }
        }
    }
    /*for (auto i:p) {
        cout << i.first << ":" << i.second << "\t";
    }
    cout << endl;*/
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int delp;
        cin >> delp;
        int n = p[delp].second + 1;//所有父节点需要减去的
        for (int j = p[delp].first; j != -1; j = p[j].first) {//向上遍历让所有减n
            p[j].second -= n;
            if (j == 0) {
                break;
            }
        }
        p[delp].first = -1;

        cout << p[0].second + 1 << endl;
        /*for (auto i : p) {
            cout << i.first << ":" << i.second << "\t";
        }
        cout << endl;*/
    }
}
