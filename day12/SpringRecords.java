import java.math.BigInteger;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Stream;

public class SpringRecords {

    public static final char operational = '.';
    public static final char damaged = '#';

    static List<ConditionRecord> condictionRecords = new ArrayList<ConditionRecord>();

    public static void main(String args[]) throws Exception {
        System.out.println("Hello, World!");

        if (args.length < 1) {
            throw new Exception("You should pass the file path. ");
        }

        Files.lines(Path.of(args[0]))
                .forEach((s) -> {
                    // System.out.println(s);
                    ConditionRecord condictionRecord = createRecordFroString(s);
                    condictionRecords.add(condictionRecord);
                    // System.out.println(condictionRecord.verify());
                });

        long sum = 0;
        for (ConditionRecord conditionRecord : condictionRecords) {
            long arrangs = countArrangemnts(conditionRecord);
            sum += arrangs;
            System.out.println(conditionRecord + " - " + arrangs + " - " + sum);
        }

        System.err.println(sum);

    }

    public static ConditionRecord createRecordFroString(String line) {
        String record = line.split(" ")[0];
        Integer[] damageCheck = (Integer[]) Stream.of(line.split(" ")[1].split(","))
                .map(Integer::valueOf)
                .toArray(Integer[]::new);

        ConditionRecord condictionRecord = new ConditionRecord(record, damageCheck);
        return condictionRecord;
    }

    public static long countArrangemnts(ConditionRecord condictionRecord) {

    	int condRes = condictionRecord.verify();
        if (condRes ==1) {
            //System.out.println(condictionRecord + " " + Arrays.toString(condictionRecord.checks()));
            return 1;
        } else {
        	if (condRes == 0)
        	{
        		return 0;
        	}

            if (condictionRecord.condition().indexOf("?", 0) < 0) {
                return 0;
            }

            String newCondWithQuestion = condictionRecord.condition().replaceFirst("\\?", "#");
            String newCondWithPeriod = condictionRecord.condition().replaceFirst("\\?", ".");

            return countArrangemnts(new ConditionRecord(newCondWithQuestion, condictionRecord.checks()))
                    + countArrangemnts(new ConditionRecord(newCondWithPeriod, condictionRecord.checks()));

        }
    }

}

record ConditionRecord(String condition, Integer[] checks) {
	


    public int verify() {

        int index = 0;
        for (Integer check : checks) {
            Integer teempCheck = check;
            boolean foundIt = false;

            if (index >= condition.length()) {
                // System.err.println("the condition is too short for the check " + teempCheck);
                return 0;
            }

            for (; index < condition.length() && !foundIt; index++) {

                char c = condition.charAt(index);

                // System.err.println("Check: " + check + "- c[" + index + "]=" + c + " - " +
                // teempCheck);

                if (c == '#') {
                    teempCheck--;
                    if (teempCheck < 0) {
                        // it means that it found too many #
                        // System.err.println("too many #");
                        return 0;
                    }
                } else {
                    if (teempCheck != 0 && teempCheck != check) {
                        if (c == '.') {// it means that it found a '.' but it hasn't found all the '#'
                            // System.err.println("it found a '.' but it hasn't found all the '#' -> " +
                            // teempCheck);
                            return 0;
                        }
                        if (c == '?') {
                            // it means that the '?" can become a "#"
                            teempCheck--;
                        }
                    } else if (teempCheck == 0) {
                        foundIt = true;
                    } else if (teempCheck == check) {
                        if (c == '?') {
                            // it means that it starts with '?" and the it can become a "#"
                            // teempCheck--;
                        	
                        	//This algortims doesn't work when it start with '?'
                        	return -1;
                        }
                    }

                }
            }

            if (index >= condition.length() && teempCheck != 0) {
                // System.err.println("the condition is too short for the check " + teempCheck);
                return 0;
            }

        }

        // if the string is not completely scanned, we risk to have some '#'
        for (; index < condition.length(); index++) {
            char c = condition.charAt(index);
            if (c == '#') {
                // it means that it found a '#' after the defition
                // System.err.println("it found a '#' after th end.");
                return 0;
            }
        }

        return 1;
    }

};