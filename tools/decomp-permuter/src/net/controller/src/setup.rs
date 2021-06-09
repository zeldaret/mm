use std::collections::HashMap;
use std::default::Default;
use std::fs::OpenOptions;

use sodiumoxide::crypto::sign;
use sodiumoxide::randombytes::randombytes;

use crate::db::{User, UserId, DB};
use crate::util::SimpleResult;
use crate::SetupOpts;

pub(crate) fn run_setup(opts: SetupOpts) -> SimpleResult<()> {
    let db_file = OpenOptions::new()
        .write(true)
        .create_new(true)
        .open(&opts.db)
        .unwrap_or_else(|e| {
            eprintln!("Cannot create database file {}: {}. Aborting.", &opts.db, e);
            std::process::exit(1);
        });

    let server_seed = sign::Seed::from_slice(&randombytes(32)).unwrap();
    let client_seed = sign::Seed::from_slice(&randombytes(32)).unwrap();

    let (server_pub_key, _) = sign::keypair_from_seed(&server_seed);
    let (client_pub_key, _) = sign::keypair_from_seed(&client_seed);

    let root_user = User {
        trusted_by: None,
        name: "root".into(),
        client_stats: Default::default(),
        server_stats: Default::default(),
    };
    let mut users_map: HashMap<UserId, User> = HashMap::new();
    users_map.insert(UserId::from_pubkey(&client_pub_key), root_user);
    let db = DB {
        users: users_map,
        func_stats: HashMap::new(),
        total_stats: Default::default(),
    };

    serde_json::to_writer(&db_file, &db)?;

    println!(
        "Setup successful!\n\n\
        Put the following in the server's config.toml:\n\n\
        priv_seed = \"{}\"\n\n\
        Put the following in the root client's pah.conf:\n\n\
        secret_key = \"{}\"\n\
        server_public_key = \"{}\"\n\
        server_address = \"server.example:port\"",
        hex::encode(server_seed),
        hex::encode(client_seed),
        hex::encode(server_pub_key)
    );
    Ok(())
}
