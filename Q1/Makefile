CC      := gcc
CCFLAGS := -Wall -Werror -pthread -g

B_TARGETS := test_trie_single_threaded test_trie_s_lock test_trie_rw_lock test_trie_hoh_lock
R_TARGETS := single_threaded s_lock rw_lock hoh_lock
ST_TARGETS := single_threaded
MT_TARGETS := s_lock rw_lock hoh_lock

test_all: $(R_TARGETS)

test_trie_rw_lock.c: test_trie_s_lock.c
	@tail -n +2 $< > $@
	@echo Updated $@

test_trie_hoh_lock.c: test_trie_s_lock.c
	@tail -n +3 $< > $@
	@echo Updated $@

$(B_TARGETS): % : %.c
	@echo Building
	$(CC) -o $@ $^ $(CCFLAGS)

$(ST_TARGETS): % : test_trie_%
	@rm -f -r ./.testout
	@mkdir .testout
	@echo "\n-------------------------------------------"
	@echo "Program Output($<):"
	@echo "-------------------------------------------"
	@-valgrind --leak-check=full --show-leak-kinds=all --log-file="./.testout/memtest_out_$<" ./$<
	@echo "\n-------------------------------------------"
	@echo "Valgrind Output($<):"
	@echo "-------------------------------------------"
	@cat ./.testout/memtest_out_$<

$(MT_TARGETS): % : test_trie_%
	@rm -f -r ./.testout
	@mkdir .testout
	@echo "\n-------------------------------------------"
	@echo "Program Output($<):"
	@echo "-------------------------------------------"
	@-valgrind --leak-check=full --show-leak-kinds=all --log-file="./.testout/memtest_out_$<" ./$<
	@echo "\n-------------------------------------------"
	@echo "Valgrind Memcheck Output($<):"
	@echo "-------------------------------------------"
	@cat ./.testout/memtest_out_$<
	@-valgrind --tool=helgrind --log-file="./.testout/heltest_out_$<" ./$< > /dev/null
	@echo "\n-------------------------------------------"
	@echo "Valgrind Helgrind Output($<):"
	@echo "-------------------------------------------"
	@cat ./.testout/heltest_out_$<

clean: 
	rm -f $(B_TARGETS)
	rm -f -r ./.testout
	rm -f -r ./test_trie_rw_lock.c
	rm -f -r ./test_trie_hoh_lock.c

# Add your rules after this point. Don't edit the things above:


update:
	rm -f -r test_trie_s_lock.c
	rm -f -r test_trie_single_threaded.c
	curl https://gist.githubusercontent.com/alphatron1999/5d3e39a3a463d349121978b8e70f8090/raw/fdba018d42132874eef3460b552cfbb62bedf891/test_trie_s_lock.c > test_trie_s_lock.c
	curl https://gist.githubusercontent.com/alphatron1999/5d3e39a3a463d349121978b8e70f8090/raw/fdba018d42132874eef3460b552cfbb62bedf891/test_trie_single_threaded.c > test_trie_single_threaded.c

wl_hoh:
	@mkdir wl -p
	@gcc wl_hoh_lock.c -o wl_hoh_lock -Wall -Werror -pthread -g -w
	@./wl_hoh_lock > /dev/null 
	@rm -f -r wl_hoh_lock

_clean:
	@rm -f -r wl
