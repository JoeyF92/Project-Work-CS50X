# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file

    # opening the argv file so we can read teams into a dictionary:
    with open(sys.argv[1], "r") as file:
        # pass the file to csv (dict- to read a dict) reader, creates a reader object we can iterate over
        reader = csv.DictReader(file)

        # for every row read, append it to the dicionary 'teams'
        for row in reader:
            # convert rating to an integer
            row['rating'] = int(row['rating'])
            teams.append(row)

    counts = {}

    # TODO: Simulate N tournaments and keep track of win counts

    # loop over teams, adding them to the counts dictionary- setting wins to zero
    for i in range(16):
        count_team = teams[i]['team']
        counts[count_team] = 0

    # now simulate N tournaments - adding +1 to the team that wins
    for i in range(N):
        # simulate tornament returns the winning team which we can match to our counts dictionary
        winner = simulate_tournament(teams)
        counts[winner] += 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    # create a counter for how many teams left in the tournament
    team_count = len(teams)

    # create a teams copy, which we just update with winning teams
    winning_teams = teams

    # a while loop, which will keep running round simulator, until there is less than 2 teams less
    while team_count >= 2:
        winning_teams = simulate_round(winning_teams)
        team_count /= 2

    # return the winning team - remember winning team is a dict, so we want to extract just the team name
    return (winning_teams[0]['team'])


if __name__ == "__main__":
    main()
