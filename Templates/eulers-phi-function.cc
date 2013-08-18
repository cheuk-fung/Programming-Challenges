void eulers_phi(int n, int *phi, int prm_cnt, int *prm)
{
    phi[1] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < prm_cnt && i * prm[j] < n; j++) {
            if (i % prm[j] == 0) {
                phi[i * prm[j]] = phi[i] * prm[j];
                break;
            } else {
                phi[i * prm[j]] = phi[i] * (prm[j] - 1);
            }
        }
    }
}

