class Module {
    constructor(parent = null, name = null) {
        if (parent != null) this.parentName = parent.name;
        else this.parentName = null;

        if (name != null) this.name = name;
        else this.name = "gamesR2simple";

        this.classes = [];
        this.functions = [];
    }
    addClass(cls) {
        this.classes[this.classes.length] = cls;
    }
    addFunc(func) {
        this.functions[this.functions.length] = func;
    }
    getParent() {
        return self.parentName;
    }
}

class Class {
    constructor(name) {
        self.name = name;
        self.methods = [MyFunc("__init__")];
    }
    addMethod(func) {
        self.methods[self.methods.length] = func;
    }
}

class MyFunc {
    constructor(name, args = null) {
        self.name = name;
        if (args != null) self.overloads = [args];
        else self.overloads = [];
    }
    addOverload(args) {
        this.overloads[this.overloads.length] = args;
    }
}

class SearchBox {
    constructor() {
        self.focus = false;
    }
    build() {
        this.element = document.getElementById("search");
    }
}

let modules = [
    Module()
];

let cls = Class("BaseGame");
cls.methods[0].addOverload([]);
modules[0].addClass(cls);

let searchbox = SearchBox();

document.addEventListener("DOMContentLoaded", function() {
    searchbox.build();
});