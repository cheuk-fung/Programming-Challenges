void calc_phi(int n, int *phi, int prm_cnt, int *prm, int *is_prm)
{
    phi[1] = 1;
    for (int i = 2; i < n; i++) {
        if (is_prm[i]) phi[i] = i - 1;
        else {
            for (int j = 0; j < prm_cnt; j++)
                if (i % prm[j] == 0) {
                    int k = i / prm[j];
                    if (k % prm[j] == 0) phi[i] = phi[k] * prm[j];
                    else phi[i] = phi[k] * (prm[j] - 1);
                    break;
                }
        }
    }
}
