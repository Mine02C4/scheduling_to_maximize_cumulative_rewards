/**
 * Scheduling to Maximize Cumulative Rewards
 *
 * This program solves a route optimization problem using dynamic programming.
 * Given a map with N locations, each with rewards and time-varying stay times,
 * it finds the optimal route to maximize cumulative rewards within a time limit.
 *
 * Input File Format:
 * - Line 1: N (number of locations) T (time limit) S (number of time slots)
 * - Line 2: rewards for each location (N values)
 * - Lines 3 to N+2: travel time matrix (N+1 x N+1), where index 0 is start/end point
 * - Lines N+3 onwards: stay time matrix (N x S), where row i is stay times for location i at each time slot
 */

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct ProblemData {
    int N;          // Number of locations
    int T;          // Time limit
    int S;          // Number of time slots
    std::vector<int> rewards;                      // Rewards for each location
    std::vector<std::vector<int>> travel_time;     // Travel time matrix (N+1 x N+1)
    std::vector<std::vector<int>> stay_time;       // Stay time at each location for each time slot (N x S)
};

bool readInputFile(const std::string& filename, ProblemData& data) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return false;
    }

    std::string line;

    // Read N, T, S
    if (!std::getline(file, line)) {
        std::cerr << "Error: Cannot read first line" << std::endl;
        return false;
    }
    std::istringstream iss1(line);
    if (!(iss1 >> data.N >> data.T >> data.S)) {
        std::cerr << "Error: Invalid format in first line" << std::endl;
        return false;
    }

    // Read rewards
    if (!std::getline(file, line)) {
        std::cerr << "Error: Cannot read rewards line" << std::endl;
        return false;
    }
    std::istringstream iss2(line);
    data.rewards.resize(data.N);
    for (int i = 0; i < data.N; ++i) {
        if (!(iss2 >> data.rewards[i])) {
            std::cerr << "Error: Invalid rewards format" << std::endl;
            return false;
        }
    }

    // Read travel time matrix (N+1 x N+1)
    data.travel_time.resize(data.N + 1, std::vector<int>(data.N + 1));
    for (int i = 0; i <= data.N; ++i) {
        if (!std::getline(file, line)) {
            std::cerr << "Error: Cannot read travel time line " << i << std::endl;
            return false;
        }
        std::istringstream iss(line);
        for (int j = 0; j <= data.N; ++j) {
            if (!(iss >> data.travel_time[i][j])) {
                std::cerr << "Error: Invalid travel time format at (" << i << ", " << j << ")" << std::endl;
                return false;
            }
        }
    }

    // Read stay time matrix (N x S)
    data.stay_time.resize(data.N, std::vector<int>(data.S));
    for (int i = 0; i < data.N; ++i) {
        if (!std::getline(file, line)) {
            std::cerr << "Error: Cannot read stay time line " << i << std::endl;
            return false;
        }
        std::istringstream iss(line);
        for (int j = 0; j < data.S; ++j) {
            if (!(iss >> data.stay_time[i][j])) {
                std::cerr << "Error: Invalid stay time format at (" << i << ", " << j << ")" << std::endl;
                return false;
            }
        }
    }

    return true;
}

int getTimeSlot(int current_time, int T, int S) {
    // Map current time to a time slot
    int slot_duration = (T + S - 1) / S;  // Ceiling division
    int slot = current_time / slot_duration;
    return std::min(slot, S - 1);
}

/**
 * Dynamic Programming Solution using bitmask DP
 *
 * State: dp[visited_mask][last_location][current_time] = max reward
 *
 * Due to memory constraints, we use a map to store only reachable states.
 *
 * Transition:
 *   From state (mask, loc, time) with reward r,
 *   for each unvisited location next_loc:
 *     new_time = time + travel_time[loc+1][next_loc+1] + stay_time[next_loc][time_slot]
 *     if new_time + travel_time[next_loc+1][0] <= T:
 *       update dp[mask | (1 << next_loc)][next_loc][new_time]
 */
void solve(const ProblemData& data) {
    int N = data.N;
    int T = data.T;
    int S = data.S;

    // State: (visited_mask, last_location, time) -> max_reward, path
    // Using map with tuple keys for sparse storage

    struct State {
        int reward;
        std::vector<int> path;
    };

    // For small N, use bitmask DP
    if (N > 20) {
        std::cerr << "Error: N too large for bitmask DP (max 20)" << std::endl;
        return;
    }

    // dp[mask][loc] stores best (time, reward, path) pairs
    // We need to track time because stay times are time-dependent
    std::map<std::tuple<int, int, int>, State> dp;

    // Initial state: at start point (index 0 in travel matrix), time 0, no locations visited
    dp[{0, -1, 0}] = {0, {}};

    int best_reward = 0;
    std::vector<int> best_path;

    // Process states in order of increasing time
    std::vector<std::tuple<int, int, int>> states_to_process;
    states_to_process.push_back({0, -1, 0});

    size_t process_idx = 0;
    while (process_idx < states_to_process.size()) {
        auto [mask, loc, time] = states_to_process[process_idx++];

        auto it = dp.find({mask, loc, time});
        if (it == dp.end()) continue;

        State current = it->second;

        // Check if we can return to start from current location
        int return_time;
        if (loc == -1) {
            return_time = 0;  // Already at start
        } else {
            return_time = data.travel_time[loc + 1][0];
        }

        if (time + return_time <= T) {
            // Valid complete path
            if (current.reward > best_reward) {
                best_reward = current.reward;
                best_path = current.path;
            }
        }

        // Try visiting each unvisited location
        for (int next_loc = 0; next_loc < N; ++next_loc) {
            if (mask & (1 << next_loc)) continue;  // Already visited

            // Calculate travel time to next location
            int travel;
            if (loc == -1) {
                travel = data.travel_time[0][next_loc + 1];
            } else {
                travel = data.travel_time[loc + 1][next_loc + 1];
            }

            int arrival_time = time + travel;

            // Get stay time based on arrival time slot
            int time_slot = getTimeSlot(arrival_time, T, S);
            int stay = data.stay_time[next_loc][time_slot];

            int new_time = arrival_time + stay;

            // Check if we can still return to start within time limit
            int return_from_next = data.travel_time[next_loc + 1][0];
            if (new_time + return_from_next > T) continue;

            int new_mask = mask | (1 << next_loc);
            int new_reward = current.reward + data.rewards[next_loc];

            auto key = std::make_tuple(new_mask, next_loc, new_time);
            auto existing = dp.find(key);

            if (existing == dp.end() || existing->second.reward < new_reward) {
                std::vector<int> new_path = current.path;
                new_path.push_back(next_loc);
                dp[key] = {new_reward, new_path};
                states_to_process.push_back(key);
            }
        }
    }

    // Output results
    std::cout << "Maximum Reward: " << best_reward << std::endl;
    std::cout << "Optimal Route: Start";
    for (int loc : best_path) {
        std::cout << " -> Location " << (loc + 1);
    }
    std::cout << " -> End" << std::endl;

    // Output detailed schedule
    std::cout << "\nDetailed Schedule:" << std::endl;
    int current_time = 0;
    int current_loc = -1;  // Start point
    int total_reward = 0;

    for (int next_loc : best_path) {
        int travel;
        if (current_loc == -1) {
            travel = data.travel_time[0][next_loc + 1];
        } else {
            travel = data.travel_time[current_loc + 1][next_loc + 1];
        }

        current_time += travel;
        std::cout << "  Time " << current_time << ": Arrive at Location " << (next_loc + 1) << std::endl;

        int time_slot = getTimeSlot(current_time, T, S);
        int stay = data.stay_time[next_loc][time_slot];
        current_time += stay;
        total_reward += data.rewards[next_loc];

        std::cout << "  Time " << current_time << ": Leave Location " << (next_loc + 1)
                  << " (Stay: " << stay << ", Reward: " << data.rewards[next_loc]
                  << ", Cumulative: " << total_reward << ")" << std::endl;

        current_loc = next_loc;
    }

    // Return to start
    int return_travel;
    if (current_loc == -1) {
        return_travel = 0;
    } else {
        return_travel = data.travel_time[current_loc + 1][0];
    }
    current_time += return_travel;
    std::cout << "  Time " << current_time << ": Return to End point" << std::endl;
    std::cout << "\nTotal Time Used: " << current_time << " / " << T << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    ProblemData data;
    if (!readInputFile(argv[1], data)) {
        return 1;
    }

    std::cout << "Problem loaded: " << data.N << " locations, Time limit: " << data.T
              << ", Time slots: " << data.S << std::endl;
    std::cout << std::endl;

    solve(data);

    return 0;
}
