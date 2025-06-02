mod configs;

use configs::load_configs;

fn main() {
    // Load configurations
    let cfg = load_configs();

    // Print the loaded settings
    println!("Debug mode: {}", cfg.debug);
    println!("Runtime: {}", cfg.runtime);
}
