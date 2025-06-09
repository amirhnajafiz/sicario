# EPaxos

EPaxos (Egalitarian Paxos) is a leaderless consensus protocol designed to improve upon Multi-Paxos by increasing parallelism and reducing latency—especially in geo-distributed systems.

## Features

- Leaderless: Any replica can propose commands; there's no single point of contention.
- Fast-path for non-conflicting operations: If a command doesn't conflict with others, it can be committed in just one round-trip.
- Conflict resolution: Conflicting commands are serialized using dependency tracking (like a DAG).
- Optimized for performance in systems where most operations don't conflict (e.g., key-value stores).
- Byzantine-fault not tolerated: EPaxos assumes crash-fault tolerance (like Raft and Paxos), not Byzantine faults like PBFT.
