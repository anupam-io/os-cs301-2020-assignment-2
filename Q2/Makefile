all_targets:= compile run plotting clean show

all: ${all_targets}

compile:
	@echo "Compiling..."
	@gcc main.c

run:
	@echo "Running..."
	@./a.out > outputs.csv

plotting:
	@echo "Plotting..."
	@rm -r -f plots
	@mkdir plots
	@python3 hr_graph.py
	@python3 perf_graph.py

clean:
	@rm -r -f a.out
	@rm -r -f outputs.csv
	@rm -r -f timings.csv
	@echo "All Cleaned."

show:
	@google-chrome --new-window --disable-gpu --disable-software-rasterizer -kiosk Solutions.md &