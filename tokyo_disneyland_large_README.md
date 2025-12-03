# Tokyo Disneyland Large Test Data (T=S)

This file (`tokyo_disneyland_large_input.txt`) is a larger Tokyo Disneyland test data where T=S (time limit equals number of time slots).

## Parameters

- **N = 15**: Number of attractions
- **T = 120**: Time limit in minutes
- **S = 120**: Number of time slots (T=S, each minute is a separate time slot)

## Attractions (Locations)

| Index | Attraction | Area | Reward |
|-------|------------|------|--------|
| 0 | Entrance/Exit (World Bazaar) | - | - |
| 1 | Space Mountain | Tomorrowland | 95 |
| 2 | Splash Mountain | Critter Country | 90 |
| 3 | Big Thunder Mountain | Westernland | 85 |
| 4 | Haunted Mansion | Fantasyland | 75 |
| 5 | Pirates of the Caribbean | Adventureland | 80 |
| 6 | Pooh's Hunny Hunt | Fantasyland | 88 |
| 7 | Monsters, Inc. Ride & Go Seek | Tomorrowland | 70 |
| 8 | Star Tours | Tomorrowland | 65 |
| 9 | Jungle Cruise | Adventureland | 60 |
| 10 | It's a Small World | Fantasyland | 55 |
| 11 | Buzz Lightyear's Astro Blasters | Tomorrowland | 72 |
| 12 | Roger Rabbit's Car Toon Spin | Toontown | 68 |
| 13 | Gadget's Go Coaster | Toontown | 62 |
| 14 | Western River Railroad | Adventureland | 58 |
| 15 | Country Bear Theater | Westernland | 50 |

## Key Features

- **T=S Design**: Each time slot represents exactly 1 minute, providing fine-grained time-dependent stay times
- **Cyclic Wait Patterns**: Stay times follow cyclic patterns simulating crowd fluctuations throughout the day
- **15 Attractions**: Larger problem size requiring more complex optimization

## Stay Time Patterns

Stay times vary cyclically across the 120 time slots, simulating:
- Morning quiet periods (lower wait times)
- Peak periods (higher wait times)
- Multiple cycles throughout the day

## Running the Test

```bash
./scheduler tokyo_disneyland_large_input.txt
```

## Expected Output

The optimal route visits 14 out of 15 attractions within exactly 120 minutes, achieving a maximum reward of 1005 points.
