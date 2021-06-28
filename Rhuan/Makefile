progr: main.o list.o argvFunc.o geo.o controller.o shadow.o segment.o qry.o circle.o polygon.o rectangle.o svg.o util.o tree.o geometry.o meteor.o
	gcc -std=c99 -fstack-protector-all -g main.o list.o shadow.o argvFunc.o segment.o geo.o polygon.o controller.o qry.o circle.o rectangle.o svg.o util.o meteor.o geometry.o tree.o -o progr -lm

main.o: main.c list.o argvFunc.o geo.o controller.o qry.o shadow.o circle.o segment.o rectangle.o svg.o util.o tree.o geometry.o polygon.o meteor.o
	gcc -c -std=c99 -fstack-protector-all -g main.c

list.o: DataStructures/list.h DataStructures/list.c
	gcc -c -std=c99 -fstack-protector-all -g DataStructures/list.c

argvFunc.o: argvFunc.c argvFunc.h
	gcc -c -std=c99 -fstack-protector-all -g argvFunc.c

geo.o: geo.c geo.h 
	gcc -c -std=c99 -fstack-protector-all -g geo.c

controller.o: controller.c  controller.h 
	gcc -c -std=c99 -fstack-protector-all -g controller.c

qry.o: qry.c qry.h 
	gcc -c -std=c99 -fstack-protector-all -g qry.c

circle.o: GeometricForms/circle.c GeometricForms/circle.h
	gcc -c -std=c99 -fstack-protector-all -g GeometricForms/circle.c

rectangle.o: GeometricForms/rectangle.c  GeometricForms/rectangle.h  
	gcc -c -std=c99 -fstack-protector-all -g GeometricForms/rectangle.c

segment.o: GeometricForms/segment.c  GeometricForms/segment.h  
	gcc -c -std=c99 -fstack-protector-all -g GeometricForms/segment.c

polygon.o: GeometricForms/polygon.c  GeometricForms/polygon.h  
	gcc -c -std=c99 -fstack-protector-all -g GeometricForms/polygon.c

svg.o: svg.c svg.h
	gcc -c -std=c99 -fstack-protector-all -g svg.c

util.o: util.c  util.h
	gcc -c -std=c99 -fstack-protector-all -g util.c

tree.o: DataStructures/tree.c DataStructures/tree.h 
	gcc -c -std=c99 -fstack-protector-all -g DataStructures/tree.c
	
geometry.o: geometry.c geometry.h
	gcc -c -std=c99 -fstack-protector-all -g geometry.c

shadow.o: shadow.c shadow.h
	gcc -c -std=c99 -fstack-protector-all -g shadow.c

meteor.o: meteor.c meteor.h
	gcc -c -std=c99 -fstack-protector-all -g meteor.c