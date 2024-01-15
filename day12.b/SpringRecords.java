import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.stream.Stream;

public class SpringRecords {

    public static final char operational = '.';
    public static final char damaged = '#';

    static HashMap<String, Long> duplicates = new HashMap<>();

    static List<ConditionRecord> condictionRecords = new ArrayList<ConditionRecord>();

    public static void main(String args[]) throws Exception {
        System.out.println("Hello, World!");

        if (args.length < 1) {
            throw new Exception("You should pass the file path. ");
        }

        Files.lines(Path.of(args[0])).forEach((s) -> {
            // System.out.println(s);
            ConditionRecord condictionRecord = createRecordFroString(s);
            condictionRecords.add(condictionRecord);
            System.out.println(condictionRecord + " " + Arrays.toString(condictionRecord.checks()));
        });

        long sum = 0;
        int index = 1;
        for (ConditionRecord conditionRecord : condictionRecords) {
            duplicates = new HashMap<>();
            long arrangs = countArrangemnts(conditionRecord);
            sum += arrangs;
            System.out.println(index + ") " +
                    conditionRecord.condOrig() + " - " + conditionRecord.condOrig() + " - " + arrangs + " - " + sum);
            index++;
        }

        System.err.println(sum);

    }

    public static ConditionRecord createRecordFroString(String line) {
        String record = line.split(" ")[0];
        String recordX5;

        // UNFOLDING - SECOND PART
        recordX5 = record + "?" + record + "?" + record + "?" + record + "?" + record;
        String damageCheckString = line.split(" ")[1];
        damageCheckString = damageCheckString + "," + damageCheckString + "," + damageCheckString + ","+ damageCheckString + "," + damageCheckString;

        Integer[] damageCheck = Stream.of(damageCheckString.split(",")).map(Integer::valueOf)
                .toArray(Integer[]::new);

        ConditionRecord condictionRecord = new ConditionRecord(recordX5, damageCheck, record, line.split(" ")[1]);
        return condictionRecord;
    }
    
    public static void addToDuplicateMap(ConditionRecord condictionRecord, long value) {
    	duplicates.putIfAbsent(condictionRecord.condition()+Arrays.toString(condictionRecord.checks()), value);
    }

    public static long countArrangemnts(ConditionRecord condictionRecord) {

        if (condictionRecord == null
                || condictionRecord.checks() == null
                || condictionRecord.checks().length == 0)
            return 0;
        
    	if (condictionRecord.condition().isEmpty() && condictionRecord.checks().length > 0) {
    		return 0;
    	}
    	
    	String toCheckDup = condictionRecord.condition()+Arrays.toString(condictionRecord.checks());
//    	System.out.println("Chekc Cache: "+toCheckDup);
    	Long dup = duplicates.get(toCheckDup);
    	if (dup != null)
    	{
//    		System.out.println(condictionRecord.condition()+"Resused");
    		return dup;
    	}

        String condition = condictionRecord.condition();
        switch (condition.charAt(0)) {
            case '.': {
                String newCondWith = condictionRecord.condition().substring(1);
                ConditionRecord newWithHAsh = new ConditionRecord(newCondWith, condictionRecord.checks(), "", "");
                
                
              //caching
                long count = countArrangemnts(newWithHAsh);
                addToDuplicateMap(condictionRecord, count);
                
                return count;
            }
            case '#': {

                // It is going to check the next characters.
                String newCondWith = condictionRecord.condition();
                int index = 1;
                for (; index <= (condictionRecord.checks()[0] - 1) && index < newCondWith.length(); index++) {
                    if (newCondWith.charAt(index) == '?') {
                        // the ? must only be a #
                        newCondWith = newCondWith.replaceFirst("\\?", "\\#");
                    } else if (newCondWith.charAt(index) == '.') {
                        // it is an error, because it is expected to have more #
                        return 0;
                    }
                }

                // if it has found all the '#'
                if (index > (condictionRecord.checks()[0] - 1)) {
                    // if the pattern it completed
                    if (index >= newCondWith.length()) {
                        // ...and there isn't anymore number to cover
                        if (condictionRecord.checks().length == 1) {
                            return 1;
                        } else {
                            // The pattern is completed but it is expected to find more '#'
                            return 0;
                        }
                    } else {
                        // if the pattern have still some characters to check ...
                        if (condictionRecord.checks().length == 1) {
                            // ... and the check array is completed, I would not expect to find any '#'
                            for (; index < newCondWith.length(); index++) {
                                if (newCondWith.charAt(index) == '#') {
                                    // thre are too many #
                                    return 0;
                                }
                                if (newCondWith.charAt(index) == '?') {
                                    newCondWith = newCondWith.replaceFirst("\\?", "\\.");
                                }
                            }

                            // There are only '.' and '?'
                            return 1;

                        } else {
                        	//next character must be a '.' or a '?'
                        	if (newCondWith.charAt(index) == '#') {
                        		return 0;
                        	}else {
                        	    
	                            // there are still string and number to cover. So, let see if the rest of the
	                            // pattern string has a possibility
	                            Integer c[] = Arrays.copyOfRange(condictionRecord.checks(), 1,
	                                    condictionRecord.checks().length);
	                            newCondWith = newCondWith.substring(index+1);
	                            ConditionRecord newWithHAsh = new ConditionRecord(newCondWith, c, "", "");
	                            
	                           
	                            //caching
	                            long count = countArrangemnts(newWithHAsh);
	                            addToDuplicateMap(newWithHAsh, count);
	                            
	                            return count;
	                            
                        	}
                        }

                    }
                } else {
                    // it means that index >= newCondWith.length()
                    return 0;
                }

            }
            case '?': {
                // there are 2 possibilities. It can a '.' or can be a '#'.
            	
                // case '.'
                String newCondWith = condictionRecord.condition().substring(1);
                ConditionRecord newWithHAsh = new ConditionRecord(newCondWith, condictionRecord.checks(), "", "");
                long countStaritnWithPeriod = countArrangemnts(newWithHAsh);
                
                //Caching
                addToDuplicateMap(newWithHAsh, countStaritnWithPeriod);

                newCondWith = condictionRecord.condition().replaceFirst("\\?", "\\#");
                newWithHAsh = new ConditionRecord(newCondWith, condictionRecord.checks(), "", "");
                long countStaritnWithHAsh = countArrangemnts(newWithHAsh);
                
                //Caching
                addToDuplicateMap(newWithHAsh, countStaritnWithPeriod);

                return countStaritnWithPeriod + countStaritnWithHAsh;

            }
            default:
                return 0;

        }
    }

//    public static long countArrangemnts2(ConditionRecord condictionRecord) {
//
//        if (condictionRecord == null
//                || condictionRecord.checks() == null
//                || condictionRecord.checks().length == 0)
//            return 0;
//
//        int condRes = condictionRecord.verify();
//        if (condRes == 1) {
//            // System.out.println(condictionRecord + " " +
//            // Arrays.toString(condictionRecord.checks()));
//            return 1;
//        } else {
//            if (condRes == 0) {
//                return 0;
//            }
//            int indexQuestion = condictionRecord.condition().indexOf("?", 0);
//            if (indexQuestion < 0) {
//                return 0;
//            }
//
//            if (indexQuestion == (condictionRecord.condition().length() - 1)) {
//                // if the string is a #, then CondRes would have been 1.
//                // it menash that the string is a '.', so return 0;
//                return 0;
//            }
//
//            // # is the characte
//            String newCondWith = condictionRecord.condition().substring(indexQuestion + 1);
//            Integer[] c = null;
//            if (condictionRecord.checks()[0] == 1) {
//
//                c = Arrays.copyOfRange(condictionRecord.checks(), 1, condictionRecord.checks().length);
//            } else {
//                c = Arrays.copyOfRange(condictionRecord.checks(), 0, condictionRecord.checks().length);
//                c[0] = c[0] - 1;
//            }
//            ConditionRecord newWithHAsh = new ConditionRecord(newCondWith, c, "", "");
//            Long valueWithHash = duplicates.get(newWithHAsh);
//            // System.out.println("Test: " + newCondWithHash.substring(indexQuestion + 1));
//            if (valueWithHash == null) {
//                valueWithHash = countArrangemnts(newWithHAsh);
//                duplicates.put(newWithHAsh, valueWithHash);
//            } else {
//                System.out
//                        .println("Reused: " + newWithHAsh.condition() + " - " + Arrays.toString(newWithHAsh.checks()));
//            }
//
//            // . is the character
//            ConditionRecord newWithpoint = new ConditionRecord(newCondWith, condictionRecord.checks(), "", "");
//            Long valueWithPeriod = duplicates.get(newWithpoint);
//            // System.out.println("Test: " + newCondWithPeriod.substring(indexQuestion+1));
//            if (valueWithPeriod == null) {
//                valueWithPeriod = countArrangemnts(newWithpoint);
//                duplicates.put(newWithpoint, valueWithPeriod);
//            } else {
//                System.out
//                        .println("Reused: " + newWithHAsh.condition() + " - " + Arrays.toString(newWithHAsh.checks()));
//            }
//
//            return valueWithHash + valueWithPeriod;
//
//        }
//    }

}

record ConditionRecord(String condition, Integer[] checks, String condOrig, String checkOri) {

	
	@Override
	public final int hashCode() {
	    
		return this.hashCode();
	}
	
    @Override
    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (other == null) {
            return false;
        }
        if (!(other instanceof ConditionRecord)) {
            return false;
        }
        ConditionRecord b = (ConditionRecord) other;

        return this.condition == b.condition && Arrays.equals(this.checks, b.checks);
    }

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

                            // This algortims doesn't work when it start with '?'
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