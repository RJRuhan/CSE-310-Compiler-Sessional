
yacc -d -y 1805017.y
echo 'Generated the parser C file as well the header file'
g++ -w -c -o y.o y.tab.c
echo 'Generated the parser object file'
flex 1805017.l
echo 'Generated the scanner C file'
g++ -w -c -o l.o lex.yy.c
echo 'Generated the scanner object file'
g++ y.o l.o -lfl -o App
echo 'All ready, running'
./App input.c