# funzip

`funzip` is a simple gem that extracts a zip file to a destination
directory. It is implemented in C++ using libzip to work around memory
leak problems with Ruby's built-in `zip`.


## Usage

```ruby
require 'funzip'

Funzip.unzip('archive.zip', '/tmp/destdir')
```


## Development

Run `rake compile` to build the gem.

```
$ rake compile
...compiling...
$ bundle exec irb
2.0.0-p247 :001 > require 'funzip'
 => true
 ```
