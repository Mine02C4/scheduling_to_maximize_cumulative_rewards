# Scheduling to Maximize Cumulative Rewards

A C++ program that solves a route optimization problem using dynamic programming.
Given a map with N locations, each with rewards and time-varying stay times,
it finds the optimal route to maximize cumulative rewards within a time limit.

## Problem Description

- You have a map with N locations to visit
- Each location has a reward value
- There are travel times between all pairs of locations (including start/end point)
- Each location has a required stay time that varies depending on when you arrive (time slots)
- You must start and end at the same point (index 0)
- You must complete your journey within a time limit T
- Goal: Maximize the total rewards collected

## Input File Format

```
N T S
r1 r2 ... rN
t(0,0) t(0,1) ... t(0,N)
t(1,0) t(1,1) ... t(1,N)
...
t(N,0) t(N,1) ... t(N,N)
s(1,1) s(1,2) ... s(1,S)
s(2,1) s(2,2) ... s(2,S)
...
s(N,1) s(N,2) ... s(N,S)
```

Where:
- `N`: Number of locations to visit
- `T`: Time limit for the entire journey
- `S`: Number of time slots (for time-varying stay times)
- `r1, r2, ..., rN`: Rewards for each location
- `t(i,j)`: Travel time from location i to location j (index 0 is start/end point)
- `s(i,j)`: Stay time at location i during time slot j

## Building

```bash
make
```

## Running

```bash
./scheduler <input_file>
```

Example:
```bash
./scheduler sample_input.txt
```

## Sample Input

See `sample_input.txt` for an example with 5 locations and a time limit of 100.

## Algorithm

The program uses **bitmask dynamic programming** to solve this optimization problem.

State: `dp[visited_mask][last_location][current_time]` = maximum reward

For each state, we try transitioning to all unvisited locations, computing:
- Travel time from current location to next location
- Stay time at next location based on arrival time slot
- New cumulative reward

The algorithm ensures that we can always return to the start point within the time limit.

## Limitations

- Maximum 20 locations (due to bitmask representation)
- Time complexity: O(2^N * N^2 * T) in worst case, but optimized with sparse state storage