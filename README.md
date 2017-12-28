# funzip

`funzip` is a simple gem that extracts a zip file to a destination
directory. It is implemented in C++ using libzip to work around memory
leak problems with Ruby's built-in `zip`.

## System prerequisites

- `libzip`

## Usage

```ruby
require 'funzip'

Funzip.unzip('archive.zip', '/tmp/destdir')
```

On success, `unzip` returns normally. On failure, `unzip` raises a
`StandardError` with a (hopefully) helpful message.


## Development

Run `bundle exec rake compile` to build the gem.

```
$ bundle exec rake compile
...compiling...
$ bundle exec irb
> require 'funzip'
 => true
```

RSpec can only be run after compiling

```
bundle exec rake compile
bundle exec rspec
```
