(*
 *  SRC: NKOJ 2181
 * PROB: Exercise 1 稳定婚姻匹配
 * ALGO: Gale-Shapley
 * DATE: Sep 22, 2011 
 * COMP: fpc
 *
 * Created by Leewings Ac
 *)

var n,i,j,head,tail,m,w:integer;
    a,b,r:array[1..30,1..30] of integer;
    p,pa,pb:array[1..30] of integer;
    q:array[0..100] of integer;
begin
    readln(n);
    for i:=1 to n do
        for j:=1 to n do
            read(a[i,j]);
    for i:=1 to n do
        for j:=1 to n do begin
            read(b[i,j]);
            r[i,b[i,j]]:=j;
        end;
    for i:=1 to n do begin
        q[i]:=i;
        p[i]:=1;
    end;
    head:=0;
    tail:=n;
    repeat
        head:=(head+1) mod 100;
        m:=q[head];
        if pa[m]=0 then begin
            w:=a[m,p[m]];
            inc(p[m]);
            if pb[w]=0 then begin
                pa[m]:=w;
                pb[w]:=m;
            end
            else if r[w,m]<r[w,pb[w]] then begin
                pa[pb[w]]:=0;
                tail:=(tail+1) mod 100;
                q[tail]:=pb[w];
                pa[m]:=w;
                pb[w]:=m;
            end
            else begin
                tail:=(tail+1) mod 100;
                q[tail]:=m;
            end;
        end;
    until head=tail;
    for i:=1 to n do write(pa[i], ' ');
    writeln();
end.
