data_av: data_av.c
	gcc data_av.c -o data_av


.PHONY: clean
clean:
	-rm -rf data_av foo *.oxs *.exe 

