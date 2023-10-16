/* Given: A sequence of numbers x1, x2, ..., xn input one-by-one, find the median
as the numbers arrive.
* The median is the middle value in an ordered integer list. If the size of the
list is even, there is no middle value and the median is the mean of the two middle
values.
* Your algorithms should be O(nlogn) where n is the number of elements seen thus
far.
* Hint: Solution involves using a max and min heap (STL priority queues) discussed
in class.
*/
#include <iostream>
#include <queue>
#include <vector>
const int MAX_VAL = 100;
const int NUM_ELEM = 15;
// Helper function to print queue for debugging
template<typename T> void printQueue(T& q) {
	T q_copy(q);
	while (!q_copy.empty()) {
		std::cout << q_copy.top() << " ";
		q_copy.pop();
	}
	std::cout << std::endl;
}
std::vector<double> findMedian(std::vector<int>& data) {
	std::priority_queue<int> max_heap; // STL Max-heap
	std::priority_queue<int, std::vector<int>, std::greater<int> > min_heap; //STL Min - heap
	std::vector<double> res;
	// Your code here
	while (!data.empty()){

		if (max_heap.empty() || data.at(0) < max_heap.top()) {
			max_heap.push(data.at(0));
		}
		else {
			min_heap.push(data.at(0));
		}
		bool min_heap_larger = (min_heap.size() - max_heap.size() == 2); // Min heap larger than max heap by two?
		bool max_heap_larger = (max_heap.size() - min_heap.size() == 2); // Max heap larger than min heap by two?

		if (min_heap_larger) {
			max_heap.push(min_heap.top());
			min_heap.pop();
		}

		if (max_heap_larger) {
			min_heap.push(max_heap.top());
			max_heap.pop();
		}

		bool amount_elements_odd = (min_heap.size() + max_heap.size()) % 2;
		if (amount_elements_odd) {
			if (max_heap.size() > min_heap.size()) {
				res.push_back(max_heap.top());
			}
			else {
				res.push_back(min_heap.top());
			}
		}
		else {
			double median = 0.5 * (min_heap.top() + max_heap.top());
			res.push_back(median);
		}
		data.erase(data.begin());
	}
	return res;
	// Please comment out any debugging print outs
}
int main() {
	std::vector<int> data_stream1 = { 5, 42, 29, 85, 95, 99, 2, 15 };
	std::vector<double> median_stream1 = findMedian(data_stream1);
	for (auto ele : median_stream1) {
		std::cout << ele << " "; // Answer should be 5 23.5 29 35.5 42 63.5 42 35.5
	}
	std::cout << std::endl;

	std::vector<int> data_stream2 = { 10, 20, 30, 40, 50, 60 };
	std::vector<double> median_stream2 = findMedian(data_stream2);
	for (auto ele : median_stream2) {
		std::cout << ele << " "; // Answer should be 10 15 20 25 30 35
	}
	std::cout << std::endl;

	std::vector<int> data_stream3 = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
	std::vector<double> median_stream3 = findMedian(data_stream3);
	for (auto ele : median_stream3) {
		std::cout << ele << " "; // Answer should be 1 2 3 4 5 4 4 4.5 5 5.5
	}
	std::cout << std::endl;

	return 0;
}

