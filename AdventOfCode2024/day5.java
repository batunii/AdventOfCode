import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.HashMap;
import java.util.Scanner;
import java.util.stream.Collectors;

public class day5 {
	static ArrayList<String> mapInputs = new ArrayList<>();
	static ArrayList<String> questionInputs = new ArrayList<>();
	static Long finalAnswer = 0L;

	public static void main(String[] args) {
		File file = new File("input5.txt");
		boolean question = false;
		try (Scanner scanner = new Scanner(file)) {

			while (scanner.hasNextLine()) {
				String line = scanner.nextLine();
				if (line.equals("<PAGE BREAK>")) {
					question = true;
					continue;
				}
				if (question)
					questionInputs.add(line);
				else
					mapInputs.add(line);

			}
			scanner.close();
		} catch (FileNotFoundException fne) {
			System.err.println("File not found");
		}

		for (int i = 0; i < questionInputs.size(); i++) {
			List<Integer> set = getHashSet(i);
			HashMap<Integer, Integer> inNodes = new HashMap<>();
			for (String maps : mapInputs) {
				Integer val1 = Integer.parseInt(maps.split("\\|")[0]);
				Integer val2 = Integer.parseInt(maps.split("\\|")[1]);
				// System.out.println(val1 + " : " + val2);
				if (set.contains(val1) && set.contains(val2)) {
					inNodes.computeIfPresent(val2, (k, v) -> ++v);
					inNodes.putIfAbsent(val2, 1);
					inNodes.putIfAbsent(val1, 0);
				}
			}
			List<Integer> orderedList = inNodes.entrySet().stream().sorted(Map.Entry.comparingByValue())
					.map(Map.Entry::getKey).collect(Collectors.toCollection(ArrayList::new));
			finalAnswer += !(compareOrder(set, orderedList)) ? orderedList.get(orderedList.size() / 2) : 0;

		}
		System.out.println(finalAnswer);

	}

	static List<Integer> getHashSet(int i) {
		List<Integer> problemSet = new ArrayList<>();
		for (String problem : questionInputs.get(i).split(",")) {
			problemSet.add(Integer.parseInt(problem));
		}
		return problemSet;
	}

	static boolean compareOrder(List<Integer> list1, List<Integer> list2) {
		if (list1.size() != list2.size())
			return false;
		for (int i = 0; i < list1.size(); i++) {
			if (list1.get(i) != list2.get(i))
				return false;
		}
		return true;
	}

}
