#include <cmath>
#include <fstream>
#include <iostream>
#include <set>

#include "csvstream.hpp"
using namespace std;

// EFFECTS: Return a set of unique whitespace delimited words
set<string> unique_words(const string& str) {
  istringstream source(str);
  set<string> words;
  string word;
  while (source >> word) {
    words.insert(word);
  }
  return words;
}

int main(int argc, char* argv[]) {
  cout.precision(3);

  if (!((argc == 2) || (argc == 3))) {
    cout << "Usage: classifier.exe TRAIN_FILE [TEST_FILE]" << endl;
    return 1;
  }

  // if (argc == 2) {
  //   string train_filename = argv[1];
  //   try {
  //     csvstream csv_train(train_filename);
  //     map<string, string> row;
  //     while (csv_train >> row) {
  //       cout << row["euchre"] << "\n";
  //     }
  //   } catch (const csvstream_exception& e) {
  //     cerr << e.what() << "\n";
  //     cout << "Error opening file: " << argv[1] << endl;
  //     return 1;
  //   }
  // } else {
  //   string train_filename = argv[1];
  //   try {
  //     csvstream csv_train(train_filename);
  //     map<string, string> row;
  //     while (csv_train >> row) {
  //       cout << row["euchre"] << "\n";
  //     }
  //   } catch (const csvstream_exception& e) {
  //     cerr << e.what() << "\n";
  //     cout << "Error opening file: " << argv[1] << endl;
  //     return 1;
  //   }
  //   string test_filename = argv[2];
  //   try {
  //     csvstream csv_test(train_filename);
  //     map<string, string> row;
  //     while (csv_test >> row) {
  //       cout << row["euchre"] << "\n";
  //     }
  //   } catch (const csvstream_exception& e) {
  //     cerr << e.what() << "\n";
  //     cout << "Error opening file: " << argv[2] << endl;
  //     return 1;
  //   }
  // }

  csvstream csv_train(argv[1]);

  int num_post = 0;  // The total number of posts in the entire training set.
  set<string> unique_word;  // The number of unique words in the entire training
                            // set. (The vocabulary size.)
  map<string, int> word_count;  // For each word w, the number of posts in the
                                // entire training set that contain w
  map<string, int>
      label_count;  // For each label C, the number of posts with that label.
  map<string, map<string, int>>
      label_w_post;  // For each label C and word w , the number of posts
                     //  with label C that contain W

  if (argc == 2) {
    cout << "training data:" << "\n";
    vector<pair<string, string>> row;
    while (csv_train >> row) {
      const string& label_data = row[2].second;
      cout << "  " << "label = " << label_data << ", ";
      const string& content_data = row[3].second;
      cout << "content = " << content_data << "\n";
      set<string> words = unique_words(content_data);

      label_count[label_data]++;

      for (string word : words) {
        unique_word.insert(word);
        word_count[word]++;
        label_w_post[label_data][word]++;
      }

      num_post++;
    }
    cout << "trained on " << num_post << " examples" << "\n";
    cout << "vocabulary size = " << unique_word.size() << "\n";
    cout << "\n";
    cout << "classes:" << "\n";

    for (const auto& pair : label_count) {
      double log_prior =
          log(static_cast<double>(pair.second) / static_cast<double>(num_post));
      cout << "  " << pair.first << ", " << pair.second
           << " examples, log-prior = " << log_prior << endl;
    }

    cout << "classifier parameters:" << "\n";
    for (const auto& outer_pair : label_w_post) {
      for (const auto& inner_pair : outer_pair.second) {
        double log_likeli =
            log(static_cast<double>(inner_pair.second) /
                static_cast<double>(label_count[outer_pair.first]));
        cout << "  " << outer_pair.first << ":";
        cout << inner_pair.first << ", count = " << inner_pair.second
             << ", log-likelihood = " << log_likeli << endl;
      }
    }

    cout << "\n";
  }
  if (argc == 3) {
    // train init
    vector<pair<string, string>> train_row;
    while (csv_train >> train_row) {
      const string& label_data = train_row[2].second;
      const string& content_data = train_row[3].second;
      set<string> words = unique_words(content_data);

      label_count[label_data]++;

      for (string word : words) {
        unique_word.insert(word);
        word_count[word]++;
        label_w_post[label_data][word]++;
      }

      num_post++;
    }

    // train training
    map<string, double> log_prior_map;  // pass in label, and you get the Pc
    map<string, map<string, double>> log_likeli_map;
    map<string, double> log_prob_score; // score you get after going through test senteces

    // log_prior["eucre"] ->

    for (const auto& pair : label_count) {
      double log_prior =
          log(static_cast<double>(pair.second) / static_cast<double>(num_post));
      log_prior_map[pair.first] = log_prior;
    }

    // cout << "log prior " << log_prior_map["euchre"] << "\n";
    // cout << "log prior " << log_prior_map["calculator"] << "\n";

    for (const auto& outer_pair : label_w_post) {
      for (const auto& inner_pair : outer_pair.second) {
        double log_likeli =
            log(static_cast<double>(inner_pair.second) /
                static_cast<double>(label_count[outer_pair.first]));
        log_likeli_map[outer_pair.first][inner_pair.first] = log_likeli;
      }
    }

    // cout << "log_likeli " << log_likeli_map["euchre"]["ever"] << "\n";

    csvstream csv_test(argv[2]);
    vector<pair<string, string>> test_row;

    cout << "trained on " << num_post << " examples" << "\n";
    cout << "\n";
    cout << "test data:" << "\n";

    while (csv_test >> test_row) {
      const string& label_data = test_row[2].second;
      // first add ln P(C)
      double log_prob_value = log_prior_map[label_data];

      // then add ln P(w|C)
      const string& content_data = test_row[3].second;
      set<string> test_words = unique_words(content_data);

      // loop through each of the words
      for (string test_word : test_words) {
        double log_add_value = 0;
        if (label_w_post[label_data].count(test_word) > 0) {
          log_add_value = log_likeli_map[label_data][test_word];
        } else if (word_count.count(test_word) > 0) {
          log_add_value = log(static_cast<double>(word_count[test_word]) /
                              static_cast<double>(num_post)); 
        } else {
          log_add_value = log(1.0 / static_cast<double>(num_post));
        }
        log_prob_value = log_prob_value + log_add_value;
        log_prob_score[label_data] = log_prob_value;
      }

      cout << "  " << "correct = " << label_data
           << ", predicted = " << ", log-probability score = " << log_prob_value
           << "\n";
      cout << "  " << "content = " << content_data << "\n";
      cout << "\n";
    }
    cout << "performance: " << "\n";
  }
}

// for (unsigned int i = 0; i < row.size(); ++i) {
//   const string& column_name = row[i].first;
//   const string& datum = row[i].second;
//   cout << "  " << column_name << ": " << datum << "\n";
// }