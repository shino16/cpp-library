#!/usr/bin/bash

cd .verify-helper/markdown
bundle install --path .vendor/bundle
bundle add webrick
bundle exec jekyll serve --incremental
