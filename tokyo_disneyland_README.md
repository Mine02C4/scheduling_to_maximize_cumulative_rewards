# Tokyo Disneyland Test Data

This file (`tokyo_disneyland_input.txt`) models a day at Tokyo Disneyland as test data for the scheduling optimization program.

## Parameters

- **N = 10**: Number of attractions
- **T = 600**: Time limit in minutes (10 hours at the park, 9:00 - 19:00)
- **S = 4**: Time slots representing different parts of the day

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

## Rewards

Rewards are based on attraction popularity on a 1-100 scale. Higher rewards indicate more popular/satisfying attractions.

## Travel Times

Travel times represent approximate walking distances between attractions in minutes. Nearby attractions (e.g., within the same area) have shorter travel times.

## Time Slots

The stay time (wait time + ride time) varies by time slot:

| Slot | Time Period | Description |
|------|-------------|-------------|
| 1 | 9:00 - 11:00 | Morning - Shorter waits |
| 2 | 11:00 - 13:00 | Late Morning - Medium waits |
| 3 | 13:00 - 17:00 | Afternoon - Peak waits |
| 4 | 17:00 - 19:00 | Evening - Decreasing waits |

## Running the Test

```bash
./scheduler tokyo_disneyland_input.txt
```

## Expected Output

The optimal route visits all 10 attractions within 600 minutes, achieving a maximum reward of 763 points with approximately 500 minutes of total time used.
