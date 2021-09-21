/*
-------- Real DFT / Inverse of Real DFT --------
    [definition]
        <case1> RDFT
            R[k] = sum_j=0^n-1 a[j]*cos(2*pi*j*k/n), 0<=k<=n/2
            I[k] = sum_j=0^n-1 a[j]*sin(2*pi*j*k/n), 0<k<n/2
        <case2> IRDFT (excluding scale)
            a[k] = (R[0] + R[n/2]*cos(pi*k))/2 + 
                   sum_j=1^n/2-1 R[j]*cos(2*pi*j*k/n) + 
                   sum_j=1^n/2-1 I[j]*sin(2*pi*j*k/n), 0<=k<n
    [usage]
        <case1>
            ip[0] = 0; // first time only
            rdft(n, 1, a, ip, w);
        <case2>
            ip[0] = 0; // first time only
            rdft(n, -1, a, ip, w);
    [parameters]
        n              :data length (int)
                        n >= 2, n = power of 2
        a[0...n-1]     :input/output data (float *)
                        <case1>
                            output data
                                a[2*k] = R[k], 0<=k<n/2
                                a[2*k+1] = I[k], 0<k<n/2
                                a[1] = R[n/2]
                        <case2>
                            input data
                                a[2*j] = R[j], 0<=j<n/2
                                a[2*j+1] = I[j], 0<j<n/2
                                a[1] = R[n/2]
        ip[0...*]      :work area for bit reversal (int *)
                        length of ip >= 2+sqrt(n/2)
                        strictly, 
                        length of ip >= 
                            2+(1<<(int)(log(n/2+0.5)/log(2))/2).
                        ip[0],ip[1] are pointers of the cos/sin table.
        w[0...n/2-1]   :cos/sin table (float *)
                        w[],ip[] are initialized if ip[0] == 0.
    [remark]
        Inverse of 
            rdft(n, 1, a, ip, w);
        is 
            rdft(n, -1, a, ip, w);
            for (j = 0; j <= n - 1; j++) {
                a[j] *= 2.0 / n;
            }
        .

Appendix :
    The cos/sin table is recalculated when the larger table required.
    w[] and ip[] are compatible with all routines.
*/


    int nw, nc, nwh, nch, k, k1, l, j, m, m2;
    float delta, x, y;
    int j1, j2, j3, j4, j5, j6, j7;
    float wn4r, x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i,
        y0r, y0i, y1r, y1i, y2r, y2i, y3r, y3i,
        y4r, y4i, y5r, y5i, y6r, y6i, y7r, y7i;
	float wtmp, wk1r, wk1i, wk2r, wk2i, wk3r, wk3i,
        wk4r, wk4i, wk5r, wk5i, wk6r, wk6i, wk7r, wk7i;
	int kk, ks;
	float wkr, wki, xr, xi, yr, yi;

#include "fft8g.h"
void rdft(int n, int isgn, union ADDATA *a, int *ip, union ADDATA *w)
{
    void makewt(int nw, int *ip, union ADDATA *w);
    void makect(int nc, int *ip, union ADDATA *c);
    void bitrv2(int n, int *ip, union ADDATA *a);
    void cftfsub(int n, union ADDATA *a, union ADDATA *w);
    void rftfsub(int n, union ADDATA *a, int nc, union ADDATA *c);
    
    nw = ip[0];
    if (n > (nw << 2)) {
        nw = n >> 2;
        makewt(nw, ip, w);
    }
    nc = ip[1];
    if (n > (nc << 2)) {
        nc = n >> 2;
        makect(nc, ip, w + nw);
    }
            bitrv2(n, ip + 2, a);
            cftfsub(n, a, w);
            rftfsub(n, a, nc, w + nw);
        xi = a[0].f - a[1].f;
        a[0].f += a[1].f;
        a[1].f = xi;
}

/* -------- initializing routines -------- */


#include <math.h>

void makewt(int nw, int *ip, union ADDATA *w)
{
    void bitrv2(int n, int *ip, union ADDATA *a);
    
    ip[0] = nw;
    ip[1] = 1;
    if (nw > 2) {
        nwh = nw >> 1;
        delta = atan(1.0) / nwh;
        w[0].f = 1;
        w[1].f = 0;
        w[nwh].f = cos(delta * nwh);
        w[nwh + 1].f = w[nwh].f;
        if (nwh > 2) {
            for (j = 2; j < nwh; j += 2) {
                x = cos(delta * j);
                y = sin(delta * j);
                w[j].f = x;
                w[j + 1].f = y;
                w[nw - j].f = y;
                w[nw - j + 1].f = x;
            }
            for (j = nwh - 2; j >= 2; j -= 2) {
                x = w[2 * j].f;
                y = w[2 * j + 1].f;
                w[nwh + j].f = x;
                w[nwh + j + 1].f = y;
            }
            bitrv2(nw, ip + 2, w);
        }
    }
}


void makect(int nc, int *ip, union ADDATA *c)
{
    
    ip[1] = nc;
    if (nc > 1) {
        nch = nc >> 1;
        delta = atan(1.0) / nch;
        c[0].f = cos(delta * nch);
        c[nch].f = 0.5 * c[0].f;
        for (j = 1; j < nch; j++) {
            c[j].f = 0.5 * cos(delta * j);
            c[nc - j].f = 0.5 * sin(delta * j);
        }
    }
}


/* -------- child routines -------- */


void bitrv2(int n, int *ip, union ADDATA *a)
{

    ip[0] = 0;
    l = n;
    m = 1;
    while ((m << 3) < l) {
        l >>= 1;
        for (j = 0; j < m; j++) {
            ip[m + j] = ip[j] + l;
        }
        m <<= 1;
    }
    m2 = 2 * m;
    if ((m << 3) == l) {
        for (k = 0; k < m; k++) {
            for (j = 0; j < k; j++) {
                j1 = 2 * j + ip[k];
                k1 = 2 * k + ip[j];
                xr = a[j1].f;
                xi = a[j1 + 1].f;
                yr = a[k1].f;
                yi = a[k1 + 1].f;
                a[j1].f = yr;
                a[j1 + 1].f = yi;
                a[k1].f = xr;
                a[k1 + 1].f = xi;
                j1 += m2;
                k1 += 2 * m2;
                xr = a[j1].f;
                xi = a[j1 + 1].f;
                yr = a[k1].f;
                yi = a[k1 + 1].f;
                a[j1].f = yr;
                a[j1 + 1].f = yi;
                a[k1].f = xr;
                a[k1 + 1].f = xi;
                j1 += m2;
                k1 -= m2;
                xr = a[j1].f;
                xi = a[j1 + 1].f;
                yr = a[k1].f;
                yi = a[k1 + 1].f;
                a[j1].f = yr;
                a[j1 + 1].f = yi;
                a[k1].f = xr;
                a[k1 + 1].f = xi;
                j1 += m2;
                k1 += 2 * m2;
                xr = a[j1].f;
                xi = a[j1 + 1].f;
                yr = a[k1].f;
                yi = a[k1 + 1].f;
                a[j1].f = yr;
                a[j1 + 1].f = yi;
                a[k1].f = xr;
                a[k1 + 1].f = xi;
            }
            j1 = 2 * k + m2 + ip[k];
            k1 = j1 + m2;
            xr = a[j1].f;
            xi = a[j1 + 1].f;
            yr = a[k1].f;
            yi = a[k1 + 1].f;
            a[j1].f = yr;
            a[j1 + 1].f = yi;
            a[k1].f = xr;
            a[k1 + 1].f = xi;
        }
    } else {
        for (k = 1; k < m; k++) {
            for (j = 0; j < k; j++) {
                j1 = 2 * j + ip[k];
                k1 = 2 * k + ip[j];
                xr = a[j1].f;
                xi = a[j1 + 1].f;
                yr = a[k1].f;
                yi = a[k1 + 1].f;
                a[j1].f = yr;
                a[j1 + 1].f = yi;
                a[k1].f = xr;
                a[k1 + 1].f = xi;
                j1 += m2;
                k1 += m2;
                xr = a[j1].f;
                xi = a[j1 + 1].f;
                yr = a[k1].f;
                yi = a[k1 + 1].f;
                a[j1].f = yr;
                a[j1 + 1].f = yi;
                a[k1].f = xr;
                a[k1 + 1].f = xi;
            }
        }
    }
}


void bitrv2conj(int n, int *ip, union ADDATA *a)
{
    
    ip[0] = 0;
    l = n;
    m = 1;
    while ((m << 3) < l) {
        l >>= 1;
        for (j = 0; j < m; j++) {
            ip[m + j] = ip[j] + l;
        }
        m <<= 1;
    }
    m2 = 2 * m;
    if ((m << 3) == l) {
        for (k = 0; k < m; k++) {
            for (j = 0; j < k; j++) {
                j1 = 2 * j + ip[k];
                k1 = 2 * k + ip[j];
                xr = a[j1].f;
                xi = -a[j1 + 1].f;
                yr = a[k1].f;
                yi = -a[k1 + 1].f;
                a[j1].f = yr;
                a[j1 + 1].f = yi;
                a[k1].f = xr;
                a[k1 + 1].f = xi;
                j1 += m2;
                k1 += 2 * m2;
                xr = a[j1].f;
                xi = -a[j1 + 1].f;
                yr = a[k1].f;
                yi = -a[k1 + 1].f;
                a[j1].f = yr;
                a[j1 + 1].f = yi;
                a[k1].f = xr;
                a[k1 + 1].f = xi;
                j1 += m2;
                k1 -= m2;
                xr = a[j1].f;
                xi = -a[j1 + 1].f;
                yr = a[k1].f;
                yi = -a[k1 + 1].f;
                a[j1].f = yr;
                a[j1 + 1].f = yi;
                a[k1].f = xr;
                a[k1 + 1].f = xi;
                j1 += m2;
                k1 += 2 * m2;
                xr = a[j1].f;
                xi = -a[j1 + 1].f;
                yr = a[k1].f;
                yi = -a[k1 + 1].f;
                a[j1].f = yr;
                a[j1 + 1].f = yi;
                a[k1].f = xr;
                a[k1 + 1].f = xi;
            }
            k1 = 2 * k + ip[k];
            a[k1 + 1].f = -a[k1 + 1].f;
            j1 = k1 + m2;
            k1 = j1 + m2;
            xr = a[j1].f;
            xi = -a[j1 + 1].f;
            yr = a[k1].f;
            yi = -a[k1 + 1].f;
            a[j1].f = yr;
            a[j1 + 1].f = yi;
            a[k1].f = xr;
            a[k1 + 1].f = xi;
            k1 += m2;
            a[k1 + 1].f = -a[k1 + 1].f;
        }
    } else {
        a[1].f = -a[1].f;
        a[m2 + 1].f = -a[m2 + 1].f;
        for (k = 1; k < m; k++) {
            for (j = 0; j < k; j++) {
                j1 = 2 * j + ip[k];
                k1 = 2 * k + ip[j];
                xr = a[j1].f;
                xi = -a[j1 + 1].f;
                yr = a[k1].f;
                yi = -a[k1 + 1].f;
                a[j1].f = yr;
                a[j1 + 1].f = yi;
                a[k1].f = xr;
                a[k1 + 1].f = xi;
                j1 += m2;
                k1 += m2;
                xr = a[j1].f;
                xi = -a[j1 + 1].f;
                yr = a[k1].f;
                yi = -a[k1 + 1].f;
                a[j1].f = yr;
                a[j1 + 1].f = yi;
                a[k1].f = xr;
                a[k1 + 1].f = xi;
            }
            k1 = 2 * k + ip[k];
            a[k1 + 1].f = -a[k1 + 1].f;
            a[k1 + m2 + 1].f = -a[k1 + m2 + 1].f;
        }
    }
}


void cftfsub(int n, union ADDATA *a, union ADDATA *w)
{
    void cft1st(int n, union ADDATA *a, union ADDATA *w);
    void cftmdl(int n, int l, union ADDATA *a, union ADDATA *w);
    
    l = 2;
        cft1st(n, a, w);
        l = 16;
        while ((l << 3) <= n) {
            cftmdl(n, l, a, w);
            l <<= 3;
        }
    if ((l << 1) < n) {
        for (j = 0; j < l; j += 2) {
            j1 = j + l;
            j2 = j1 + l;
            j3 = j2 + l;
            x0r = a[j].f + a[j1].f;
            x0i = a[j + 1].f + a[j1 + 1].f;
            x1r = a[j].f - a[j1].f;
            x1i = a[j + 1].f - a[j1 + 1].f;
            x2r = a[j2].f + a[j3].f;
            x2i = a[j2 + 1].f + a[j3 + 1].f;
            x3r = a[j2].f - a[j3].f;
            x3i = a[j2 + 1].f - a[j3 + 1].f;
            a[j].f = x0r + x2r;
            a[j + 1].f = x0i + x2i;
            a[j2].f = x0r - x2r;
            a[j2 + 1].f = x0i - x2i;
            a[j1].f = x1r - x3i;
            a[j1 + 1].f = x1i + x3r;
            a[j3].f = x1r + x3i;
            a[j3 + 1].f = x1i - x3r;
        }
    } else if ((l << 1) == n) {
        for (j = 0; j < l; j += 2) {
            j1 = j + l;
            x0r = a[j].f - a[j1].f;
            x0i = a[j + 1].f - a[j1 + 1].f;
            a[j].f += a[j1].f;
            a[j + 1].f += a[j1 + 1].f;
            a[j1].f = x0r;
            a[j1 + 1].f = x0i;
        }
    }
}


void cftbsub(int n, union ADDATA *a, union ADDATA *w)
{
    void cft1st(int n, union ADDATA *a, union ADDATA *w);
    void cftmdl(int n, int l, union ADDATA *a, union ADDATA *w);

    l = 2;
        cft1st(n, a, w);
        l = 16;
        while ((l << 3) < n) {
            cftmdl(n, l, a, w);
            l <<= 3;
        }
    if ((l << 2) < n) {
        wn4r = w[2].f;
        for (j = 0; j < l; j += 2) {
            j1 = j + l;
            j2 = j1 + l;
            j3 = j2 + l;
            j4 = j3 + l;
            j5 = j4 + l;
            j6 = j5 + l;
            j7 = j6 + l;
            x0r = a[j].f + a[j1].f;
            x0i = -a[j + 1].f - a[j1 + 1].f;
            x1r = a[j].f - a[j1].f;
            x1i = -a[j + 1].f + a[j1 + 1].f;
            x2r = a[j2].f + a[j3].f;
            x2i = a[j2 + 1].f + a[j3 + 1].f;
            x3r = a[j2].f - a[j3].f;
            x3i = a[j2 + 1].f - a[j3 + 1].f;
            y0r = x0r + x2r;
            y0i = x0i - x2i;
            y2r = x0r - x2r;
            y2i = x0i + x2i;
            y1r = x1r - x3i;
            y1i = x1i - x3r;
            y3r = x1r + x3i;
            y3i = x1i + x3r;
            x0r = a[j4].f + a[j5].f;
            x0i = a[j4 + 1].f + a[j5 + 1].f;
            x1r = a[j4].f - a[j5].f;
            x1i = a[j4 + 1].f - a[j5 + 1].f;
            x2r = a[j6].f + a[j7].f;
            x2i = a[j6 + 1].f + a[j7 + 1].f;
            x3r = a[j6].f - a[j7].f;
            x3i = a[j6 + 1].f - a[j7 + 1].f;
            y4r = x0r + x2r;
            y4i = x0i + x2i;
            y6r = x0r - x2r;
            y6i = x0i - x2i;
            x0r = x1r - x3i;
            x0i = x1i + x3r;
            x2r = x1r + x3i;
            x2i = x1i - x3r;
            y5r = wn4r * (x0r - x0i);
            y5i = wn4r * (x0r + x0i);
            y7r = wn4r * (x2r - x2i);
            y7i = wn4r * (x2r + x2i);
            a[j1].f = y1r + y5r;
            a[j1 + 1].f = y1i - y5i;
            a[j5].f = y1r - y5r;
            a[j5 + 1].f = y1i + y5i;
            a[j3].f = y3r - y7i;
            a[j3 + 1].f = y3i - y7r;
            a[j7].f = y3r + y7i;
            a[j7 + 1].f = y3i + y7r;
            a[j].f = y0r + y4r;
            a[j + 1].f = y0i - y4i;
            a[j4].f = y0r - y4r;
            a[j4 + 1].f = y0i + y4i;
            a[j2].f = y2r - y6i;
            a[j2 + 1].f = y2i - y6r;
            a[j6].f = y2r + y6i;
            a[j6 + 1].f = y2i + y6r;
        }
    } else if ((l << 2) == n) {
        for (j = 0; j < l; j += 2) {
            j1 = j + l;
            j2 = j1 + l;
            j3 = j2 + l;
            x0r = a[j].f + a[j1].f;
            x0i = -a[j + 1].f - a[j1 + 1].f;
            x1r = a[j].f - a[j1].f;
            x1i = -a[j + 1].f + a[j1 + 1].f;
            x2r = a[j2].f + a[j3].f;
            x2i = a[j2 + 1].f + a[j3 + 1].f;
            x3r = a[j2].f - a[j3].f;
            x3i = a[j2 + 1].f - a[j3 + 1].f;
            a[j].f = x0r + x2r;
            a[j + 1].f = x0i - x2i;
            a[j2].f = x0r - x2r;
            a[j2 + 1].f = x0i + x2i;
            a[j1].f = x1r - x3i;
            a[j1 + 1].f = x1i - x3r;
            a[j3].f = x1r + x3i;
            a[j3 + 1].f = x1i + x3r;
        }
    } else {
        for (j = 0; j < l; j += 2) {
            j1 = j + l;
            x0r = a[j].f - a[j1].f;
            x0i = -a[j + 1].f + a[j1 + 1].f;
            a[j].f += a[j1].f;
            a[j + 1].f = -a[j + 1].f - a[j1 + 1].f;
            a[j1].f = x0r;
            a[j1 + 1].f = x0i;
        }
    }
}


void cft1st(int n, union ADDATA *a, union ADDATA *w)
{
    
    wn4r = w[2].f;
    x0r = a[0].f + a[2].f;
    x0i = a[1].f + a[3].f;
    x1r = a[0].f - a[2].f;
    x1i = a[1].f - a[3].f;
    x2r = a[4].f + a[6].f;
    x2i = a[5].f + a[7].f;
    x3r = a[4].f - a[6].f;
    x3i = a[5].f - a[7].f;
    y0r = x0r + x2r;
    y0i = x0i + x2i;
    y2r = x0r - x2r;
    y2i = x0i - x2i;
    y1r = x1r - x3i;
    y1i = x1i + x3r;
    y3r = x1r + x3i;
    y3i = x1i - x3r;
    x0r = a[8].f + a[10].f;
    x0i = a[9].f + a[11].f;
    x1r = a[8].f - a[10].f;
    x1i = a[9].f - a[11].f;
    x2r = a[12].f + a[14].f;
    x2i = a[13].f + a[15].f;
    x3r = a[12].f - a[14].f;
    x3i = a[13].f - a[15].f;
    y4r = x0r + x2r;
    y4i = x0i + x2i;
    y6r = x0r - x2r;
    y6i = x0i - x2i;
    x0r = x1r - x3i;
    x0i = x1i + x3r;
    x2r = x1r + x3i;
    x2i = x1i - x3r;
    y5r = wn4r * (x0r - x0i);
    y5i = wn4r * (x0r + x0i);
    y7r = wn4r * (x2r - x2i);
    y7i = wn4r * (x2r + x2i);
    a[2].f = y1r + y5r;
    a[3].f = y1i + y5i;
    a[10].f = y1r - y5r;
    a[11].f = y1i - y5i;
    a[6].f = y3r - y7i;
    a[7].f = y3i + y7r;
    a[14].f = y3r + y7i;
    a[15].f = y3i - y7r;
    a[0].f = y0r + y4r;
    a[1].f = y0i + y4i;
    a[8].f = y0r - y4r;
    a[9].f = y0i - y4i;
    a[4].f = y2r - y6i;
    a[5].f = y2i + y6r;
    a[12].f = y2r + y6i;
    a[13].f = y2i - y6r;
        wk1r = w[4].f;
        wk1i = w[5].f;
        x0r = a[16].f + a[18].f;
        x0i = a[17].f + a[19].f;
        x1r = a[16].f - a[18].f;
        x1i = a[17].f - a[19].f;
        x2r = a[20].f + a[22].f;
        x2i = a[21].f + a[23].f;
        x3r = a[20].f - a[22].f;
        x3i = a[21].f - a[23].f;
        y0r = x0r + x2r;
        y0i = x0i + x2i;
        y2r = x0r - x2r;
        y2i = x0i - x2i;
        y1r = x1r - x3i;
        y1i = x1i + x3r;
        y3r = x1r + x3i;
        y3i = x1i - x3r;
        x0r = a[24].f + a[26].f;
        x0i = a[25].f + a[27].f;
        x1r = a[24].f - a[26].f;
        x1i = a[25].f - a[27].f;
        x2r = a[28].f + a[30].f;
        x2i = a[29].f + a[31].f;
        x3r = a[28].f - a[30].f;
        x3i = a[29].f - a[31].f;
        y4r = x0r + x2r;
        y4i = x0i + x2i;
        y6r = x0r - x2r;
        y6i = x0i - x2i;
        x0r = x1r - x3i;
        x0i = x1i + x3r;
        x2r = x1r + x3i;
        x2i = x3r - x1i;
        y5r = wk1i * x0r - wk1r * x0i;
        y5i = wk1i * x0i + wk1r * x0r;
        y7r = wk1r * x2r + wk1i * x2i;
        y7i = wk1r * x2i - wk1i * x2r;
        x0r = wk1r * y1r - wk1i * y1i;
        x0i = wk1r * y1i + wk1i * y1r;
        a[18].f = x0r + y5r;
        a[19].f = x0i + y5i;
        a[26].f = y5i - x0i;
        a[27].f = x0r - y5r;
        x0r = wk1i * y3r - wk1r * y3i;
        x0i = wk1i * y3i + wk1r * y3r;
        a[22].f = x0r - y7r;
        a[23].f = x0i + y7i;
        a[30].f = y7i - x0i;
        a[31].f = x0r + y7r;
        a[16].f = y0r + y4r;
        a[17].f = y0i + y4i;
        a[24].f = y4i - y0i;
        a[25].f = y0r - y4r;
        x0r = y2r - y6i;
        x0i = y2i + y6r;
        a[20].f = wn4r * (x0r - x0i);
        a[21].f = wn4r * (x0i + x0r);
        x0r = y6r - y2i;
        x0i = y2r + y6i;
        a[28].f = wn4r * (x0r - x0i);
        a[29].f = wn4r * (x0i + x0r);
        k1 = 4;
        for (j = 32; j < n; j += 16) {
            k1 += 4;
            wk1r = w[k1].f;
            wk1i = w[k1 + 1].f;
            wk2r = w[k1 + 2].f;
            wk2i = w[k1 + 3].f;
            wtmp = 2 * wk2i;
            wk3r = wk1r - wtmp * wk1i;
            wk3i = wtmp * wk1r - wk1i;
            wk4r = 1 - wtmp * wk2i;
            wk4i = wtmp * wk2r;
            wtmp = 2 * wk4i;
            wk5r = wk3r - wtmp * wk1i;
            wk5i = wtmp * wk1r - wk3i;
            wk6r = wk2r - wtmp * wk2i;
            wk6i = wtmp * wk2r - wk2i;
            wk7r = wk1r - wtmp * wk3i;
            wk7i = wtmp * wk3r - wk1i;
            x0r = a[j].f + a[j + 2].f;
            x0i = a[j + 1].f + a[j + 3].f;
            x1r = a[j].f - a[j + 2].f;
            x1i = a[j + 1].f - a[j + 3].f;
            x2r = a[j + 4].f + a[j + 6].f;
            x2i = a[j + 5].f + a[j + 7].f;
            x3r = a[j + 4].f - a[j + 6].f;
            x3i = a[j + 5].f - a[j + 7].f;
            y0r = x0r + x2r;
            y0i = x0i + x2i;
            y2r = x0r - x2r;
            y2i = x0i - x2i;
            y1r = x1r - x3i;
            y1i = x1i + x3r;
            y3r = x1r + x3i;
            y3i = x1i - x3r;
            x0r = a[j + 8].f + a[j + 10].f;
            x0i = a[j + 9].f + a[j + 11].f;
            x1r = a[j + 8].f - a[j + 10].f;
            x1i = a[j + 9].f - a[j + 11].f;
            x2r = a[j + 12].f + a[j + 14].f;
            x2i = a[j + 13].f + a[j + 15].f;
            x3r = a[j + 12].f - a[j + 14].f;
            x3i = a[j + 13].f - a[j + 15].f;
            y4r = x0r + x2r;
            y4i = x0i + x2i;
            y6r = x0r - x2r;
            y6i = x0i - x2i;
            x0r = x1r - x3i;
            x0i = x1i + x3r;
            x2r = x1r + x3i;
            x2i = x1i - x3r;
            y5r = wn4r * (x0r - x0i);
            y5i = wn4r * (x0r + x0i);
            y7r = wn4r * (x2r - x2i);
            y7i = wn4r * (x2r + x2i);
            x0r = y1r + y5r;
            x0i = y1i + y5i;
            a[j + 2].f = wk1r * x0r - wk1i * x0i;
            a[j + 3].f = wk1r * x0i + wk1i * x0r;
            x0r = y1r - y5r;
            x0i = y1i - y5i;
            a[j + 10].f = wk5r * x0r - wk5i * x0i;
            a[j + 11].f = wk5r * x0i + wk5i * x0r;
            x0r = y3r - y7i;
            x0i = y3i + y7r;
            a[j + 6].f = wk3r * x0r - wk3i * x0i;
            a[j + 7].f = wk3r * x0i + wk3i * x0r;
            x0r = y3r + y7i;
            x0i = y3i - y7r;
            a[j + 14].f = wk7r * x0r - wk7i * x0i;
            a[j + 15].f = wk7r * x0i + wk7i * x0r;
            a[j].f = y0r + y4r;
            a[j + 1].f = y0i + y4i;
            x0r = y0r - y4r;
            x0i = y0i - y4i;
            a[j + 8].f = wk4r * x0r - wk4i * x0i;
            a[j + 9].f = wk4r * x0i + wk4i * x0r;
            x0r = y2r - y6i;
            x0i = y2i + y6r;
            a[j + 4].f = wk2r * x0r - wk2i * x0i;
            a[j + 5].f = wk2r * x0i + wk2i * x0r;
            x0r = y2r + y6i;
            x0i = y2i - y6r;
            a[j + 12].f = wk6r * x0r - wk6i * x0i;
            a[j + 13].f = wk6r * x0i + wk6i * x0r;
        }

}


void cftmdl(int n, int l, union ADDATA *a, union ADDATA *w)
{

    m = l << 3;
    wn4r = w[2].f;
    for (j = 0; j < l; j += 2) {
        j1 = j + l;
        j2 = j1 + l;
        j3 = j2 + l;
        j4 = j3 + l;
        j5 = j4 + l;
        j6 = j5 + l;
        j7 = j6 + l;
        x0r = a[j].f + a[j1].f;
        x0i = a[j + 1].f + a[j1 + 1].f;
        x1r = a[j].f - a[j1].f;
        x1i = a[j + 1].f - a[j1 + 1].f;
        x2r = a[j2].f + a[j3].f;
        x2i = a[j2 + 1].f + a[j3 + 1].f;
        x3r = a[j2].f - a[j3].f;
        x3i = a[j2 + 1].f - a[j3 + 1].f;
        y0r = x0r + x2r;
        y0i = x0i + x2i;
        y2r = x0r - x2r;
        y2i = x0i - x2i;
        y1r = x1r - x3i;
        y1i = x1i + x3r;
        y3r = x1r + x3i;
        y3i = x1i - x3r;
        x0r = a[j4].f + a[j5].f;
        x0i = a[j4 + 1].f + a[j5 + 1].f;
        x1r = a[j4].f - a[j5].f;
        x1i = a[j4 + 1].f - a[j5 + 1].f;
        x2r = a[j6].f + a[j7].f;
        x2i = a[j6 + 1].f + a[j7 + 1].f;
        x3r = a[j6].f - a[j7].f;
        x3i = a[j6 + 1].f - a[j7 + 1].f;
        y4r = x0r + x2r;
        y4i = x0i + x2i;
        y6r = x0r - x2r;
        y6i = x0i - x2i;
        x0r = x1r - x3i;
        x0i = x1i + x3r;
        x2r = x1r + x3i;
        x2i = x1i - x3r;
        y5r = wn4r * (x0r - x0i);
        y5i = wn4r * (x0r + x0i);
        y7r = wn4r * (x2r - x2i);
        y7i = wn4r * (x2r + x2i);
        a[j1].f = y1r + y5r;
        a[j1 + 1].f = y1i + y5i;
        a[j5].f = y1r - y5r;
        a[j5 + 1].f = y1i - y5i;
        a[j3].f = y3r - y7i;
        a[j3 + 1].f = y3i + y7r;
        a[j7].f = y3r + y7i;
        a[j7 + 1].f = y3i - y7r;
        a[j].f = y0r + y4r;
        a[j + 1].f = y0i + y4i;
        a[j4].f = y0r - y4r;
        a[j4 + 1].f = y0i - y4i;
        a[j2].f = y2r - y6i;
        a[j2 + 1].f = y2i + y6r;
        a[j6].f = y2r + y6i;
        a[j6 + 1].f = y2i - y6r;
    }
    if (m < n) {
        wk1r = w[4].f;
        wk1i = w[5].f;
        for (j = m; j < l + m; j += 2) {
            j1 = j + l;
            j2 = j1 + l;
            j3 = j2 + l;
            j4 = j3 + l;
            j5 = j4 + l;
            j6 = j5 + l;
            j7 = j6 + l;
            x0r = a[j].f + a[j1].f;
            x0i = a[j + 1].f + a[j1 + 1].f;
            x1r = a[j].f - a[j1].f;
            x1i = a[j + 1].f - a[j1 + 1].f;
            x2r = a[j2].f + a[j3].f;
            x2i = a[j2 + 1].f + a[j3 + 1].f;
            x3r = a[j2].f - a[j3].f;
            x3i = a[j2 + 1].f - a[j3 + 1].f;
            y0r = x0r + x2r;
            y0i = x0i + x2i;
            y2r = x0r - x2r;
            y2i = x0i - x2i;
            y1r = x1r - x3i;
            y1i = x1i + x3r;
            y3r = x1r + x3i;
            y3i = x1i - x3r;
            x0r = a[j4].f + a[j5].f;
            x0i = a[j4 + 1].f + a[j5 + 1].f;
            x1r = a[j4].f - a[j5].f;
            x1i = a[j4 + 1].f - a[j5 + 1].f;
            x2r = a[j6].f + a[j7].f;
            x2i = a[j6 + 1].f + a[j7 + 1].f;
            x3r = a[j6].f - a[j7].f;
            x3i = a[j6 + 1].f - a[j7 + 1].f;
            y4r = x0r + x2r;
            y4i = x0i + x2i;
            y6r = x0r - x2r;
            y6i = x0i - x2i;
            x0r = x1r - x3i;
            x0i = x1i + x3r;
            x2r = x1r + x3i;
            x2i = x3r - x1i;
            y5r = wk1i * x0r - wk1r * x0i;
            y5i = wk1i * x0i + wk1r * x0r;
            y7r = wk1r * x2r + wk1i * x2i;
            y7i = wk1r * x2i - wk1i * x2r;
            x0r = wk1r * y1r - wk1i * y1i;
            x0i = wk1r * y1i + wk1i * y1r;
            a[j1].f = x0r + y5r;
            a[j1 + 1].f = x0i + y5i;
            a[j5].f = y5i - x0i;
            a[j5 + 1].f = x0r - y5r;
            x0r = wk1i * y3r - wk1r * y3i;
            x0i = wk1i * y3i + wk1r * y3r;
            a[j3].f = x0r - y7r;
            a[j3 + 1].f = x0i + y7i;
            a[j7].f = y7i - x0i;
            a[j7 + 1].f = x0r + y7r;
            a[j].f = y0r + y4r;
            a[j + 1].f = y0i + y4i;
            a[j4].f = y4i - y0i;
            a[j4 + 1].f = y0r - y4r;
            x0r = y2r - y6i;
            x0i = y2i + y6r;
            a[j2].f = wn4r * (x0r - x0i);
            a[j2 + 1].f = wn4r * (x0i + x0r);
            x0r = y6r - y2i;
            x0i = y2r + y6i;
            a[j6].f = wn4r * (x0r - x0i);
            a[j6 + 1].f = wn4r * (x0i + x0r);
        }
        k1 = 4;
        for (k = 2 * m; k < n; k += m) {
            k1 += 4;
            wk1r = w[k1].f;
            wk1i = w[k1 + 1].f;
            wk2r = w[k1 + 2].f;
            wk2i = w[k1 + 3].f;
            wtmp = 2 * wk2i;
            wk3r = wk1r - wtmp * wk1i;
            wk3i = wtmp * wk1r - wk1i;
            wk4r = 1 - wtmp * wk2i;
            wk4i = wtmp * wk2r;
            wtmp = 2 * wk4i;
            wk5r = wk3r - wtmp * wk1i;
            wk5i = wtmp * wk1r - wk3i;
            wk6r = wk2r - wtmp * wk2i;
            wk6i = wtmp * wk2r - wk2i;
            wk7r = wk1r - wtmp * wk3i;
            wk7i = wtmp * wk3r - wk1i;
            for (j = k; j < l + k; j += 2) {
                j1 = j + l;
                j2 = j1 + l;
                j3 = j2 + l;
                j4 = j3 + l;
                j5 = j4 + l;
                j6 = j5 + l;
                j7 = j6 + l;
                x0r = a[j].f + a[j1].f;
                x0i = a[j + 1].f + a[j1 + 1].f;
                x1r = a[j].f - a[j1].f;
                x1i = a[j + 1].f - a[j1 + 1].f;
                x2r = a[j2].f + a[j3].f;
                x2i = a[j2 + 1].f + a[j3 + 1].f;
                x3r = a[j2].f - a[j3].f;
                x3i = a[j2 + 1].f - a[j3 + 1].f;
                y0r = x0r + x2r;
                y0i = x0i + x2i;
                y2r = x0r - x2r;
                y2i = x0i - x2i;
                y1r = x1r - x3i;
                y1i = x1i + x3r;
                y3r = x1r + x3i;
                y3i = x1i - x3r;
                x0r = a[j4].f + a[j5].f;
                x0i = a[j4 + 1].f + a[j5 + 1].f;
                x1r = a[j4].f - a[j5].f;
                x1i = a[j4 + 1].f - a[j5 + 1].f;
                x2r = a[j6].f + a[j7].f;
                x2i = a[j6 + 1].f + a[j7 + 1].f;
                x3r = a[j6].f - a[j7].f;
                x3i = a[j6 + 1].f - a[j7 + 1].f;
                y4r = x0r + x2r;
                y4i = x0i + x2i;
                y6r = x0r - x2r;
                y6i = x0i - x2i;
                x0r = x1r - x3i;
                x0i = x1i + x3r;
                x2r = x1r + x3i;
                x2i = x1i - x3r;
                y5r = wn4r * (x0r - x0i);
                y5i = wn4r * (x0r + x0i);
                y7r = wn4r * (x2r - x2i);
                y7i = wn4r * (x2r + x2i);
                x0r = y1r + y5r;
                x0i = y1i + y5i;
                a[j1].f = wk1r * x0r - wk1i * x0i;
                a[j1 + 1].f = wk1r * x0i + wk1i * x0r;
                x0r = y1r - y5r;
                x0i = y1i - y5i;
                a[j5].f = wk5r * x0r - wk5i * x0i;
                a[j5 + 1].f = wk5r * x0i + wk5i * x0r;
                x0r = y3r - y7i;
                x0i = y3i + y7r;
                a[j3].f = wk3r * x0r - wk3i * x0i;
                a[j3 + 1].f = wk3r * x0i + wk3i * x0r;
                x0r = y3r + y7i;
                x0i = y3i - y7r;
                a[j7].f = wk7r * x0r - wk7i * x0i;
                a[j7 + 1].f = wk7r * x0i + wk7i * x0r;
                a[j].f = y0r + y4r;
                a[j + 1].f = y0i + y4i;
                x0r = y0r - y4r;
                x0i = y0i - y4i;
                a[j4].f = wk4r * x0r - wk4i * x0i;
                a[j4 + 1].f = wk4r * x0i + wk4i * x0r;
                x0r = y2r - y6i;
                x0i = y2i + y6r;
                a[j2].f = wk2r * x0r - wk2i * x0i;
                a[j2 + 1].f = wk2r * x0i + wk2i * x0r;
                x0r = y2r + y6i;
                x0i = y2i - y6r;
                a[j6].f = wk6r * x0r - wk6i * x0i;
                a[j6 + 1].f = wk6r * x0i + wk6i * x0r;
            }
        }
    }
}


void rftfsub(int n, union ADDATA *a, int nc, union ADDATA *c)
{
    
    m = n >> 1;
    ks = 2 * nc / m;
    kk = 0;
    for (j = 2; j < m; j += 2) {
        k = n - j;
        kk += ks;
        wkr = 0.5 - c[nc - kk].f;
        wki = c[kk].f;
        xr = a[j].f - a[k].f;
        xi = a[j + 1].f + a[k + 1].f;
        yr = wkr * xr - wki * xi;
        yi = wkr * xi + wki * xr;
        a[j].f -= yr;
        a[j + 1].f -= yi;
        a[k].f += yr;
        a[k + 1].f -= yi;
    }
}


void rftbsub(int n, union ADDATA *a, int nc, union ADDATA *c)
{
    
    a[1].f = -a[1].f;
    m = n >> 1;
    ks = 2 * nc / m;
    kk = 0;
    for (j = 2; j < m; j += 2) {
        k = n - j;
        kk += ks;
        wkr = 0.5 - c[nc - kk].f;
        wki = c[kk].f;
        xr = a[j].f - a[k].f;
        xi = a[j + 1].f + a[k + 1].f;
        yr = wkr * xr + wki * xi;
        yi = wkr * xi - wki * xr;
        a[j].f -= yr;
        a[j + 1].f = yi - a[j + 1].f;
        a[k].f += yr;
        a[k + 1].f = yi - a[k + 1].f;
    }
    a[m + 1].f = -a[m + 1].f;
}

