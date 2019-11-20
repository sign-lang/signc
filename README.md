# Sign - signc

## Building locally

```
make [all]
make install
make clean
```

###### Environment Variables

- `DEBUG=1` build with debug symbols
- `SIGN_HOST` put artifacts in a sub folder
- `SIGN_INSTALL_PATH` (default: `bin`) control where `make install` copies the binary

###### Intermediate Stages

```
make stage1
make stage2
make stage3
make signc
make clean-bin
```

## Building in Docker

```
docker run --volume `pwd`:/sign --workdir /sign -it signlang/base:<version> make <target>
```

If `Docker` is cloned in the same folder as `signc` the following make targets become available:

```
make all/<version>
make install/<version>
```

To make all docker versions:

```
make all/docker
make install/docker
```
