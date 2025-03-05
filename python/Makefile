# Conda specific Makefile
SHELL := /bin/bash
.SHELLFLAGS := -eu -o pipefail -c
MAKEFLAGS += --error-undefined-variables
MAKEFLAGS += --no-builtin-rules

.DEFAULT_GOAL := help

# Global variables
DSAVENV := venv
PY_PACKAGE_NAME := $(shell python -c "import tomli; print(tomli.load(open('pyproject.toml', 'rb'))['project']['name'])" | xargs | sed 's/-/_/g')
PY_PACKAGE_VERSION := $(shell python -c "import tomli; print(tomli.load(open('pyproject.toml', 'rb'))['project']['version'])" | xargs)
sources = vim_dsa tests

.PHONY: build debug create-venv pack-venv venv-publish bump-dev-ver bump-major-ver bump-patch-ver bump-minor-ver pypi-publish format lint typecheck codespell test test-pypath testcov help docs  ## Run the standard set of checks performed in CI

debug: ## Shows all variables and syntax errors of this Makefile
	$(foreach v, $(.VARIABLES), $(warning $(v) = $($(v))))

test-pypath: ## Once you have all your third-party dependencies installed, instead of installing all your packages,you can append some file system paths to the PYTHONPATH environment variable. This will let Python search for packages in those paths without installing the packages.
	@python3 -c 'import sys; print(sys.path)'

create-venv: ## Creates virtual environment(s) venv & venv_dev in conda environment for build activities
	$(info Creating virtual environments - [${DSAVENV}_dev, ${DSAVENV}] in conda environment)
	@conda remove --name $(DSAVENV) --all -y && conda remove --name $(DSAVENV)_dev --all -y
	@conda create --name $(DSAVENV) python=3.10 conda-pack -y && conda update --name $(DSAVENV) --update-all -y python=3.10 conda-pack
	@conda init --all && . ~/.zshrc || true . ~/.bashrc || true && conda activate $(DSAVENV) && pip install .[venv-pkgs] --no-build-isolation --ignore-installed && conda deactivate
	@conda create --name $(DSAVENV)_dev python=3.10 conda-pack -y && conda update --name $(DSAVENV)_dev --update-all -y python=3.10 conda-pack
	@conda init --all && . ~/.zshrc || true . ~/.bashrc || true && conda activate $(DSAVENV)_dev && pip install -e .[venv-pkgs,dev,test,lint] --no-build-isolation --ignore-installed && conda deactivate

build: ## Builds the PYPI package for distribution & publish
	@rm -rf ./dist ./sdist
	@conda init --all && . ~/.zshrc || true . ~/.bashrc || true && conda activate $(DSAVENV)_dev && python -m build && conda deactivate

pack-venv: ## Packs virtual environment into a zip file for deploying into artifactory
	$(info Packing virtual environment $(DSAVENV) into $(DSAVENV)-$(PY_PACKAGE_VERSION).tar.gz)
	$(info Usage in pyspark: $(DSAVENV)-$(PY_PACKAGE_VERSION).tar.gz#$(DSAVENV))
	@conda init --all && . ~/.zshrc || true . ~/.bashrc || true && conda activate $(DSAVENV) && conda pack -f -o ./$(DSAVENV)-$(PY_PACKAGE_VERSION).tar.gz && conda deactivate

bump-dev-version: ## PRNUM=<GIT_PR_NUMBER> Bumps dev release versions example 0.1.1 to 0.1.1.dev6 the digit 6 is PR number
	@git tag -d v$(PY_PACKAGE_VERSION) || true && git tag v$(PY_PACKAGE_VERSION)
	@git commit --allow-empty -m "ci: update-version:dev-release"
	@conda init --all && . ~/.zshrc || true . ~/.bashrc || true && conda activate $(DSAVENV)_dev && cz bump --files-only --yes --devrelease ${PR_NUM} --bump-message "ci: update-versions:dev-release" && conda deactivate

bump-patch-version: ## Bumps patch release versions example 0.1.1 to 0.1.2; the right most digit
	@git remote update && git fetch --verbose && git pull && git checkout ${BRANCH}
	@conda init --all && . ~/.zshrc || true . ~/.bashrc || true && conda activate $(DSAVENV)_dev && cz bump --yes --increment PATCH --bump-message "ci: update-versions:patch-release" && conda deactivate

bump-minor-version: ## Bumps minor release versions example 0.1.5 to 0.2.0; the center digit
	@git remote update && git fetch --verbose && git pull && git checkout ${BRANCH}
	@conda init --all && . ~/.zshrc || true . ~/.bashrc || true && conda activate $(DSAVENV)_dev && cz bump --yes --increment MINOR --bump-message "ci: update-versions:minor-release" && conda deactivate

bump-major-version: ## Bumps major release versions example 1.1.3 to 2.0.0; the left most digit
	@git remote update && git fetch --verbose && git pull && git checkout ${BRANCH}
	@conda init --all && . ~/.zshrc || true . ~/.bashrc || true && conda activate $(DSAVENV)_dev && cz bump --yes --increment MAJOR --bump-message "ci: update-versions:major-release" && conda deactivate

pypi-publish: ## PYPI_REPO=<artifactoru-URL> to Publish to given PYPI artifactory
	$(info Publishing $(shell ls ./dist/*) to $(PYPI_REPO))
	@conda init --all && . ~/.zshrc || true . ~/.bashrc || true && conda activate $(DSAVENV)_dev && twine upload --repository-url ${PYPI_REPO} dist/* --verbose && conda deactivate
	@curl -X PUT -u ${reposolnsUsername}:${reposolnsPassword} "${GENERIC_REPO}/${PY_PACKAGE_NAME}/main/${PY_PACKAGE_VERSION}/main.py" -T ./main.py -v --fail
	@curl -X PUT -u ${reposolnsUsername}:${reposolnsPassword} "${GENERIC_REPO}/${PY_PACKAGE_NAME}/main/${PY_PACKAGE_VERSION}/main.py" -T ./main.py -v --fail

venv-publish: ## GENERIC_REPO=<artifactoru-URL> to Publish virtual environment to given generic artifactory
	@curl -X PUT -u ${reposolnsUsername}:${reposolnsPassword} "${GENERIC_REPO}/${PY_PACKAGE_NAME}/${PY_PACKAGE_VERSION}/venv/${DSAVENV}-${PY_PACKAGE_VERSION}.tar.gz" -T ./$(DSAVENV)-$(PY_PACKAGE_VERSION).tar.gz -v --fail

pre-commit: ## Check that pre-commit is installed
	@conda init --all && . ~/.zshrc || true . ~/.bashrc || true && conda activate $(DSAVENV)_dev && pre-commit -V || echo 'Please install pre-commit: https://pre-commit.com/ pip install pre-commit or add pre-commit in pyproject.toml' && conda deactivate

format: ## Auto-format python source files
	@conda init --all && . ~/.zshrc || true . ~/.bashrc || true && conda activate $(DSAVENV)_dev && ruff --fix $(sources) && ruff format $(sources) && conda deactivate

lint: ## Lint python source files
	@conda init --all && . ~/.zshrc || true . ~/.bashrc || true && conda activate $(DSAVENV)_dev && ruff check $(sources) && ruff format --check $(sources) && conda deactivate

codespell: ## Use Codespell to do spellchecking
	@conda init --all && . ~/.zshrc || true . ~/.bashrc || true && conda activate $(DSAVENV)_dev && pre-commit run codespell --all-files && conda deactivate

typecheck: ## Perform type-checking
	@conda init --all && . ~/.zshrc || true . ~/.bashrc || true && conda activate $(DSAVENV)_dev && pre-commit run typecheck --all-files && conda deactivate

test: ## Run all tests, skipping the type-checker integration tests
	@conda init --all && . ~/.zshrc || true . ~/.bashrc || true && conda activate $(DSAVENV)_dev && coverage run -m pytest --durations=10 && conda deactivate

test-coverage: ## Run tests and generate a coverage report, skipping the type-checker integration tests
	@$(info Building coverage html, xml & lcov)
	@conda init --all && . ~/.zshrc || true . ~/.bashrc || true && conda activate $(DSAVENV)_dev && coverage xml && conda deactivate

clean: ## Clear local caches and build artifacts
	rm -rf `find . -name __pycache__`
	rm -f `find . -type f -name '*.py[co]'`
	rm -f `find . -type f -name '*~'`
	rm -f `find . -type f -name '.*~'`
	rm -rf .cache .pytest_cache .ruff_cache
	rm -rf htmlcov && rm -f .coverage && rm -f .coverage.* && rm -rf coverage.xml
	rm -rf *.egg-info
	rm -rf dist ./target build
	rm -rf docs/_build docs/.changelog.md docs/.version.md docs/.tmp_schema_mappings.html
	rm -rf ./$(DSAVENV) ./$(DSAVENV)*
	rm -f ./*.zip ./*.tar.gz
	mkdir -p ./logs
	echo $PATH && conda init --all && . ~/.zshrc || true && . ~/.bashrc || true && conda activate && conda deactivate

docs:  ## Generate the docs
	@conda init --all && . ~/.zshrc || true && . ~/.bashrc || true && conda activate $(DSAVENV)_dev && mkdocs build --strict

help: ## Display this message
	$(info Requires `pip install build` and python packaging & distribution environment: conda / miniconda / anaconda)
	@grep -E '^.*:\s+##' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":|## "}; {printf "make \033[36m%-19s\033[0m %s\n", $$1, $$3}'
