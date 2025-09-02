class Broadcaster {
    constructor() {
        document.addEventListener("DOMContentLoaded", () => this.init());
    }

    async init() {
        await this.getTimeLeft();
    }
    
    async getTimeLeft() {
        this.timeLeft = (await (await fetch("/get_time_left")).json()).time;
    }
    
    async psuedoInterval() {
        this.getTimeLeft();
        //if (timeLeft <= 30)
    }
}

new Broadcaster()