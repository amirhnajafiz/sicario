mod defaults;

use config::Config;
use serde::Deserialize;
use dotenv::dotenv;

use crate::configs::defaults::{default_debug, default_runtime};

// This struct represents the configs for the application.
#[derive(Debug, Deserialize)]
pub struct Configs {
    #[serde(default = "default_debug", rename = "MYAPP_DEBUG")]
    pub debug: bool,

    #[serde(default = "default_runtime", rename = "MYAPP_RUNTIME")]
    pub runtime: String,
}

// This function loads configurations from environment variables and .env files.
pub fn load_configs() -> Configs {
    dotenv().ok(); // loads from .env file into std::env

    let cfg = Config::builder()
        .add_source(config::Environment::default()) // reads from env vars
        .build()
        .unwrap()
        .try_deserialize::<Configs>()
        .unwrap();

    return cfg;
}
