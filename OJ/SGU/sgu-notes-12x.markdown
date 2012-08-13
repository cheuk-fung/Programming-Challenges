120\. Archipelago  
Find the center $(x\_c, y\_c)$ of the N-gon using the two given points.
Then we can calculate the next point $(x', y')$ counterclockwise based
on $(x, y)$:
\\\[
\theta = \frac{2\pi}{n},\quad
\begin{bmatrix} x' \\\\ y' \end{bmatrix} =
\begin{bmatrix}
\cos\theta & -\sin\theta \\\\
\sin\theta & \cos\theta
\end{bmatrix}
\begin{bmatrix} x - x\_c \\\\ y - y\_c \end{bmatrix} +
\begin{bmatrix}x\_c \\\\ y\_c \end{bmatrix}
\\\]
Add an offset(e.g. 1e-12) to a floating number to avoid outputting
**-0.000000**.
