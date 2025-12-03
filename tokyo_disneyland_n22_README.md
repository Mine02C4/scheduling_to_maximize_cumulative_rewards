# Tokyo Disneyland N=22 Test Data (T=S=40)

This file (`tokyo_disneyland_n22_input.txt`) is a Tokyo Disneyland test data with N=22 locations and T=S=40.

## Parameters

- **N = 22**: Number of attractions
- **T = 40**: Time limit in minutes
- **S = 40**: Number of time slots (T=S, each minute is a separate time slot)

## Attractions (Locations)

| Index | Attraction | Reward |
|-------|------------|--------|
| 1 | Space Mountain | 95 |
| 2 | Splash Mountain | 90 |
| 3 | Big Thunder Mountain | 85 |
| 4 | Haunted Mansion | 75 |
| 5 | Pirates of the Caribbean | 80 |
| 6 | Pooh's Hunny Hunt | 88 |
| 7 | Monsters, Inc. Ride & Go Seek | 70 |
| 8 | Star Tours | 65 |
| 9 | Jungle Cruise | 60 |
| 10 | It's a Small World | 55 |
| 11 | Buzz Lightyear's Astro Blasters | 72 |
| 12 | Roger Rabbit's Car Toon Spin | 68 |
| 13 | Gadget's Go Coaster | 62 |
| 14 | Western River Railroad | 58 |
| 15 | Country Bear Theater | 50 |
| 16 | Mickey's PhilharMagic | 78 |
| 17 | Cinderella's Fairy Tale Hall | 66 |
| 18 | The Enchanted Tiki Room | 74 |
| 19 | Swiss Family Treehouse | 82 |
| 20 | Tom Sawyer Island Rafts | 56 |
| 21 | Castle Carrousel | 64 |
| 22 | Dumbo the Flying Elephant | 52 |

## Key Features

- **N=22 Locations**: Near the maximum supported by bitmask DP (max 20), this tests algorithmic limits
- **T=S=40 Design**: Each time slot represents exactly 1 minute
- **Compact Travel Times**: Travel times range from 1-5 minutes between attractions
- **Low Stay Times**: Stay times are 1-2 minutes to allow visiting more locations within the time limit

## Running the Test

```bash
./scheduler tokyo_disneyland_n22_input.txt
```

## Notes

- This dataset with N=22 is supported by the 64-bit bitmask DP implementation (max 30 locations)
- Due to the exponential nature of the algorithm (O(2^N)), execution time may be very long for N>20
- This dataset is intended for benchmarking and stress testing purposes
