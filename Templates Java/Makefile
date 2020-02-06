ALL-PROBLEMS := A B C D E F G H I J K

all: $(addsuffix .class, $(ALL-PROBLEMS))

new-all: $(addsuffix .new, $(ALL-PROBLEMS))

clean:
	rm *.class

%.new:
	cp Main.java $*.java
	sed -i 's/Main/$*/g' $*.java

%.class: %.java
	javac --release 11 $<

%.run: %.class
	java $*

A: A.run
B: B.run
C: C.run
D: D.run
E: E.run
F: F.run
G: G.run
H: H.run
I: I.run
J: J.run
K: K.run
