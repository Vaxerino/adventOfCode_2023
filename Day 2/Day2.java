import java.io.*;
import java.lang.module.FindException;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class Day2 {
    ArrayList<String> lines;

    public Day2(String fileName) {
        try {
            lines = (ArrayList<String>) Files.readAllLines(new File(fileName).toPath());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public int solvePt1(int numRed, int numGreen, int numBlue) {
        return lines.stream()
                .map(Game::parseFromString)
                .map(Game::solve)
                .filter(game -> game.maxRed <= numRed && game.maxGreen <= numGreen && game.maxBlue <= numBlue)
                .reduce(0, (i, g) -> i + g.id, (Integer::sum));
    }

    public int solvePt2() {
        return lines.stream()
                .map(Game::parseFromString)
                .map(Game::solve)
                .map(game -> game.maxRed * game.maxGreen * game.maxBlue)
                .reduce(0, Integer::sum, Integer::sum);
    }

    private static class Game {
        int id;
        String gameInfo;
        int maxRed, maxGreen, maxBlue;
        private static final Pattern gamePattern = Pattern.compile("Game (\\d*)");
        private static final Pattern redPattern = Pattern.compile("(\\d*) red");
        private static final Pattern greenPattern = Pattern.compile("(\\d*) green");
        private static final Pattern bluePattern = Pattern.compile("(\\d*) blue");

        public static Game parseFromString(String input) {
            String[] parts = input.split(":");
            Game result = new Game();
            Matcher g = gamePattern.matcher(parts[0]);
            if (g.find()) {
                result.id = Integer.parseInt(g.group(1));
            } else {
                throw new FindException("No Game id found");
            }

            result.gameInfo = parts[1];
            return result;
        }

        public static Game solve(Game game) {
            String[] rounds = game.gameInfo.split(";");
            for (String round : rounds) {
                Matcher red = redPattern.matcher(round);
                if (red.find()) {
                    int parsed = Integer.parseInt(red.group(1));
                    game.maxRed = Math.max(game.maxRed, parsed);
                }
                Matcher green = greenPattern.matcher(round);
                if (green.find()) {
                    int parsed = Integer.parseInt(green.group(1));
                    game.maxGreen = Math.max(game.maxGreen, parsed);
                }
                Matcher blue = bluePattern.matcher(round);
                if (blue.find()) {
                    int parsed = Integer.parseInt(blue.group(1));
                    game.maxBlue = Math.max(game.maxBlue, parsed);
                }
            }
            return game;
        }
    }

    public static void main(String[] args) {

        Day2 day2 = new Day2("/home/simon/Coding/AdventOfCode/Day 2/input.txt");
        System.out.println(day2.solvePt1(12, 13, 14));
        System.out.println(day2.solvePt2());

    }
}
