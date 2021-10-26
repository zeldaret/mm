# controller

This directory contains code for the central permuter@home controller server,
written in Rust. All p@h traffic passes through here.

If you just want to run a regular p@h server, you don't need to care about this.

To setup your own copy of the controller server:

- Install Rust and (for the libsodium dependency) GCC.
- Run `cargo build --release`.
- Run `./target/release/pahserver setup --db path/to/database.json` and follow
  the instructions there. This will set the `priv_seed` part of `config.toml`, and
  set up an initial trusted client. The rest of `config.toml` can be copied from
  `config_example.toml`.
- Set up a reverse proxy that forwards HTTPS traffic from an external port or route
  to HTTP for a port of your choice, e.g. using Nginx or Traefik.
  If applicable, configure your firewall to let the external port through.
- Start the server with:
  ```
./target/release/pahserver run --listen-on 0.0.0.0:<port> --config config.toml --db path/to/database.json
```
and configure the system to run this at startup.
