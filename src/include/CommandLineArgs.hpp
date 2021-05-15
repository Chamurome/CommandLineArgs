#pragma once
#include <iostream>
#include <cstring>
#include <cwchar>
#include <vector>
#include <map>
#include <type_traits>

namespace mmo
{

template<typename _Char>
struct CommandLineOption;

template<typename _Char>
class CommanLineArgs;



namespace __mmo
{
template<typename _Char, typename _Traits=std::char_traits<_Char>>
struct commandline_help {};

template<>
struct commandline_help<char> {
    static constexpr const char mark = '-';

    static bool
    equal(
        const char                          *a,
        const char                          *b
    ) {
        return (strcmp(a,b)==0);
    }

    static void
    option_required(
        const char*                    appName,
        const char*                    opt
    ) {
        std::cerr << appName << ": Option '" << opt << "' required.\n";
        exit(1);
    }

    static void
    arguments_required(
        const char*                     appName,
        int                             req,
        int                             prov
    ) {
        std::cerr << appName << ": Required " << req << " arguemnts, " << prov << " provided.\n";
        exit(1);
    }


};
template<>
struct commandline_help<wchar_t> {
    static constexpr const wchar_t mark = L'-';

    static bool
    equal(
        const wchar_t                       *a,
        const wchar_t                       *b
    ) {
        return (wcscmp(a,b)==0);
    }


    static void
    option_required(
        const wchar_t*                  appName,
        const wchar_t*                  opt
    ) {
        std::wcerr << appName << L": Option '" << opt << L"' required.\n";
        exit(1);
    }

    static void
    arguments_required(
        const wchar_t*                  appName,
        int                             req,
        int                             prov
    ) {
        std::wcerr << appName << L": Required " << req << L" arguemnts, " << prov << L" provided.\n";
        exit(1);
    }
};


} // namespace __mmo


template<typename _Char>
struct CommandLineOption {
    using char_type =                       _Char;


    const char_type                         *name;
    const char_type                         *value;
    const bool                              required;

    CommandLineOption(
        const char_type                     *name,
        const char_type                     *defaultValue,
        bool                                required = false
    ):  name(name),
        value(defaultValue),
        required(required)
    {}

    CommandLineOption(
        const char_type                     *name,
        bool                                required = false
    ):  name(name),
        value(nullptr),
        required(required)
    {}


}; // struct CommandLineOption


template<typename _Char>
class CommanLineArgs {
    using help_ =                           __mmo::commandline_help<_Char>;
public:
    using char_type=                        _Char;
    using option_type =                     CommandLineOption<char_type>;


    static constexpr const char             mark = help_::mark;

    CommanLineArgs(
        const char_type                     *appName,
        std::initializer_list<option_type>  lst,
        std::size_t                         freeArgs = 0
    )
    {
        appName_ = appName;
        for(auto &it:lst) opts_.push_back(it);
        minArgs_ = freeArgs + 1; // path argument
    }

    const char_type*
    operator()(
        const char_type                     *name
    ) {
        auto it = findOption_(name);
        return ( it==opts_.end() ) ? nullptr: it->value;
    }

    const char_type*
    operator()(
        int                                 index
    ) {
        return ( index>=args_.size() ) ? nullptr: args_[index];
    }


    void
    arguments(
        int                                 argc,
        const char_type*                    argv[]
    ) {
        for(int i=0; i<argc; ++i) {
            if(is_option_(argv[i])) {
                auto it = findOption_(argv[i]);
                if( it == opts_.end() ) {
                    std::cout << "Bar argument";
                    exit(1);
                }
                if( ( (i + 1) < argc ) && (argv[i+1][0] != mark) ) {
                    it->value = argv[i+1];
                    ++i;
                }
            } else {
                args_.push_back(argv[i]);
            }
        }
        check_();
    }

    auto
    optionBegin()
    {
        return opts_.begin();
    }

    auto
    optionEnd()
    {
        return opts_.end();
    }

    auto
    argumentBegin()
    {
        return args_.begin();
    }

    auto
    argumentEnd()
    {
        return args_.end();
    }

private:
    const char_type                         *appName_;
    std::vector<option_type>                opts_;
    std::vector<const char_type*>           args_;
    std::size_t                             minArgs_;

    auto
    findOption_(
        const char_type                     *name
    ) {
        for(auto it=opts_.begin(); it!=opts_.end(); ++it) {
            if( help_::equal(it->name, name) ) return it;
        }
        return opts_.end();
    }

    bool
    is_option_(
        const char_type*                    &arg
    ) {
        if(arg[0]== mark) {
            ++arg;
            if(arg[0]== mark) ++arg;
            return true;
        }
        return false;
    }

    void check_()
    {
        for(auto &it:opts_) {
            if( it.required && (it.value == nullptr ) ) {
                help_::option_required(appName_, it.name);
            }
        }
        if( (minArgs_ > 1) && (args_.size()< minArgs_) ) {
            help_::arguments_required(appName_, minArgs_, args_.size());
        }
    }


};



} // namespace mmo
