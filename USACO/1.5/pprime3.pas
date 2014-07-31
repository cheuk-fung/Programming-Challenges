{
ID:os.idea1
PROG:pprime
LANG:PASCAL
}
program pprime;
 var i,j,k,q,a,b,s:longint;
function isok(x:longint):boolean;
   var i:longint;
   begin
    if x=1 then begin isok:=false; exit; end;
    for i:=2 to trunc(sqrt(x)) do
       if x mod i=0 then begin isok:=false;  exit;  end;
     isok:=true;
   end;
 begin
    assign(input,'pprime.in'); assign(output,'pprime.out');
    reset(input); rewrite(output);
    readln(a,b);
        for q:=0 to 9 do
            begin
              s:=q;
              if (a<=s)and(s<=b)and(isok(s)) then writeln(s);
              if (s=7)and(a<11)and(11<b) then writeln('11');
            end;
       for k:=0 to 9 do
          for q:=0 to 9 do
            begin
              s:=k*1+q*10+k*100;
              if (a<=s)and(s<=b)and(isok(s)) then writeln(s);
              if s=7 then writeln('11');
            end;
       for j:=0 to 9 do
        for k:=0 to 9 do
          for q:=0 to 9 do
            begin
              s:=j+k*10+q*100+k*1000+j*10000;
              if (a<=s)and(s<=b)and(isok(s)) then writeln(s);
              if s=7 then writeln('11');
            end;
    for i:=0 to 9 do
      for j:=0 to 9 do
        for k:=0 to 9 do
          for q:=0 to 9 do
            begin
              s:=i+j*10+k*100+q*1000+k*10000+j*100000+i*1000000;
              if (a<=s)and(s<=b)and(isok(s)) then writeln(s);
               if s=7 then writeln('11');
            end;
    close(input); close(output);
 end.