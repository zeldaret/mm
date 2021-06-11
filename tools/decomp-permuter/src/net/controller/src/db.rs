use std::collections::HashMap;
use std::convert::TryInto;

use hex::FromHex;
use serde::{Deserialize, Deserializer, Serialize, Serializer};
use serde_tuple::{Deserialize_tuple, Serialize_tuple};
use sodiumoxide::crypto::sign;

#[derive(Clone, Debug, Hash, Eq, PartialEq)]
pub struct ByteString<const SIZE: usize>([u8; SIZE]);

impl<const SIZE: usize> ByteString<SIZE> {
    fn to_hex(&self) -> String {
        hex::encode(&self.0)
    }

    fn from_hex(string: &str) -> Result<ByteString<SIZE>, &'static str> {
        Ok(ByteString(
            Vec::from_hex(&string)
                .map_err(|_| "not a valid hex string")?
                .try_into()
                .map_err(|_| "byte string has wrong size")?,
        ))
    }
}

impl<const SIZE: usize> Serialize for ByteString<SIZE> {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        serializer.serialize_str(&self.to_hex())
    }
}

impl<'de, const SIZE: usize> Deserialize<'de> for ByteString<SIZE> {
    fn deserialize<D>(deserializer: D) -> Result<ByteString<SIZE>, D::Error>
    where
        D: Deserializer<'de>,
    {
        use serde::de::Error;
        let string = String::deserialize(deserializer)?;
        ByteString::from_hex(&string).map_err(Error::custom)
    }
}

pub type UserId = ByteString<32>;

impl UserId {
    pub fn from_pubkey(key: &sign::PublicKey) -> UserId {
        ByteString(key.as_ref().try_into().unwrap())
    }

    pub fn to_pubkey(&self) -> sign::PublicKey {
        sign::PublicKey::from_slice(&self.0).unwrap()
    }
}

impl<const SIZE: usize> ByteString<SIZE> {
    pub fn to_seed(&self) -> sign::Seed {
        sign::Seed::from_slice(&self.0).unwrap()
    }
}

#[derive(Debug, Deserialize_tuple, Serialize_tuple)]
pub struct Stats {
    pub iterations: u64,
    pub improvements: u64,
    pub matches: u64,
    pub functions: u64,
}

impl Default for Stats {
    fn default() -> Stats {
        Stats {
            iterations: 0,
            improvements: 0,
            matches: 0,
            functions: 0,
        }
    }
}

#[derive(Debug, Deserialize, Serialize)]
pub struct User {
    pub trusted_by: Option<UserId>,
    pub name: String,
    pub client_stats: Stats,
    pub server_stats: Stats,
}

#[derive(Debug, Deserialize, Serialize)]
pub struct DB {
    pub users: HashMap<UserId, User>,
    pub func_stats: HashMap<String, Stats>,
    pub total_stats: Stats,
}

impl DB {
    pub fn func_stat(&mut self, fn_name: String) -> &mut Stats {
        self.func_stats
            .entry(fn_name)
            .or_insert_with(Stats::default)
    }
}
