SHELL 	:= /bin/bash

build: ## Build the tools
	@cc ttcalc.c -o ttcalc
	@cc bolocalc.c -o bolocalc

clean: ## Delete the executables
	@rm ttcalc bolocalc

tt: ## Launch the time-tagged telecommands management tool
	@./ttcalc

bolo: ## Launch the bolometers inibition management tool
	@./bolocalc

help: ## Show this help
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'