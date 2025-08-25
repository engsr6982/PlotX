/**
 * C++ std::optional
 */
declare type optional<T> = T | null;

/**
 * C++ std::vector
 */
declare type vector<T> = Array<T>;

/**
 * C++ std::unordered_map
 */
declare type unordered_map<K extends string, V> = {
    [key: string]: V;
};

/**
 * C++ std::variant
 * @usage type MyType = variant<[number, string]>;
 */
declare type variant<Args extends readonly unknown[]> = Args[number];
