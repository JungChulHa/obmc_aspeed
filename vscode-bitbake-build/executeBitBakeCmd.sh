#!/bin/bash
. ./oe-init-build-env vscode-bitbake-build > /dev/null
bitbake-layers show-appends