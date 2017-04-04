def remove_duplicate_symbols(string):
    """
    Returns string without duplicate symbols.
     
    >>> remove_duplicate_symbols('aaa')
    'a'
    
    >>> remove_duplicate_symbols('aa11b')
    'a1b'
    
    >>> remove_duplicate_symbols('AAbbfssdfffdfdfafffff656656555')
    'Abfsda65'
    
    """
    original_list = list(string)
    distinct_list = []
    for each in original_list:
        if each not in distinct_list:
            distinct_list.append(each)
    return ''.join(distinct_list)


if __name__ == '__main__':
    import doctest
    doctest.testmod()