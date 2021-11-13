YACC = bison
LEX = flex
PREFIX := hma

code: hma_lex.cpp hma_parser.cpp hma_parser.hpp

hma_parser.cpp : hma.y hma_defs.h 
	$(YACC) -d -o hma_parser.cpp  -p $(PREFIX) guido.y

hma_parser.hpp : hma.y hma_defs.h 
	$(YACC) -d -o hma_parser.cpp  -p $(PREFIX) guido.y

hma_lex.cpp : hma.l hma_defs.h hma_parser.hpp
	$(LEX)  -ohma_lex.cpp -I -P$(PREFIX) hma.l

clean:
	rm -f $(OUT)
