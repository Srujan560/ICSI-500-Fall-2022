#Let complie all at once 

final:
	gcc server.c -o s; 
	gcc client.c -o c;
	gcc encode.c -o e;
	gcc parity.c -o p;
	gcc decode.c -o d;
	gcc parityremove.c -o pr;
	gcc clinetEcoder.c -o ce;
	gcc hamming.c -o h;
	gcc errorHandling.c -o eh;
	gcc clinetDecoder.c -o cd;
	gcc serverDecoder.c -o sd;
	gcc -pthread serverPthread.c -o sp;
	gcc serverEncode.c -o se;
runServer:
	./s
runClient:
	./c
clean:
	rm *.o
removeOutputfiles:
	rm s c e p d pr ce h eh cd sd sp se
# current:
# 	gcc -pthread serverPthread.c -o sp;
# 	./sp;

