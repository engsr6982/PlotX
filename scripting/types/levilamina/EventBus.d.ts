declare module "levilamina" {
    import { Player } from "minecraft";

    interface _EventMap_ {
        // TODO: Add more events
        PlayerJoinEvent: PlayerJoinEvent;
    }
    type _EventNames_ = keyof _EventMap_;

    export type EventListener<
        N extends _EventNames_,
        E extends _EventMap_[N]
    > = (event: E) => void;

    export type EventListenerId = number;

    export class EventBus {
        static emplaceListener<N extends _EventNames_, E extends _EventMap_[N]>(
            eventName: N,
            listener: EventListener<N, E>,
            priority?: number // default: 0
        ): EventListenerId;

        static removeListener(listenerId: EventListenerId): boolean;

        static publish<E extends _EventMap_[_EventNames_]>(event: E): void;
    }

    // Event declaration
    export class Event {
        getId(): string;
    }

    export class CancellableEvent extends Event {
        isCancelled(): boolean;

        setCancelled(cancelled: boolean): void;

        cancel(): void;
    }

    export class PlayerJoinEvent extends CancellableEvent {
        self(): Player;
    }
}
